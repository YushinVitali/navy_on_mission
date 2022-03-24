#include "aircraft.hpp"

#include <windows.h>

#include <cassert>
#include <cmath>

#include "aircraft_carrier.hpp"
#include "vector2.hpp"

#include "common/collision.hpp"
#include "common/common.hpp"

#include "../framework/draw_debug.hpp"
#include "../framework/common_constants.hpp"


void Aircraft::init( AircraftCarrier* aircraftCarrier, Vector2 const& startPosition, Vector2 const& forwardVector )
{
	assert( !m_mesh );
	assert( ( aircraftCarrier ) && "Transferred to nullptr as an aircraft carrier!" );
	assert( ( !isNearlyEqual( m_takeOffTime, 0.0f ) || 0.0f > m_takeOffTime ) && "Takeoff time cannot be less than or equal to 0!" );
	assert( ( m_takeOffTime < m_flightTime ) && "Takeoff time cannot be longer than the entire flight time!" );

	m_mesh = scene::createAircraftMesh();
	m_aircraftCarrier = aircraftCarrier;
	
	m_position = startPosition;

	m_currentTarget = m_aircraftCarrier->getTarget();
	m_forwardVector = forwardVector;

	const auto direction{ m_position - ( m_position + 1.0f * m_forwardVector ) };
	m_angle = -1 * getDirectionalCoefficientOfRotation( direction ) * std::acos( m_forwardVector.x );

	m_angleWhenCirclingOverTarget = PI / 4;

	currentPointIndexAtLanding = static_cast<int64_t>(m_aircraftCarrier->getLandingTrajectory().size()) - 1;
}


void Aircraft::deinit()
{
	scene::destroyMesh( m_mesh );
	m_mesh = nullptr;
	m_aircraftCarrier = nullptr;
}


void Aircraft::update( float dt )
{
	m_timeInAction += dt;

	switch (m_state)
	{
		case ActionProcesses::TakingOff:
		{
			Takeoff( dt );
			break;
		}
		case ActionProcesses::FollowingToTarget:
		case ActionProcesses::CirclingOverTarget:
		{
			OnMission( dt );
			break;
		}
		case ActionProcesses::ReturnToHangar:
		{
			ReturnToHangar( dt );
			break;
		}
		case ActionProcesses::Landing:
			Landing( dt );
			break;
		default:
			break;
	}

	m_position = m_position + m_velocity * dt * m_forwardVector;

	scene::placeMesh( m_mesh, m_position.x, m_position.y, m_angle );
}


Vector2 Aircraft::getForwardVector() const
{
	return m_forwardVector;
}


Vector2 Aircraft::getPosition() const
{
	return m_position;
}


void Aircraft::Takeoff( float dt )
{
	const float acceleration{ params::ship::LINEAR_SPEED / m_takeOffTime };
	m_velocity += acceleration * dt;

	clamp<float>( m_velocity, 0.0f, params::ship::LINEAR_SPEED );

	if ( m_timeInAction > m_takeOffTime )
	{
		m_state = ActionProcesses::FollowingToTarget;
		m_aircraftCarrier->ReportRunwayClearance();
	}
}

void Aircraft::OnMission( float dt )
{
	if ( m_currentTarget != m_aircraftCarrier->getTarget() )
	{
		m_currentTarget = m_aircraftCarrier->getTarget();
		m_state = ActionProcesses::FollowingToTarget;
	}

	switch ( m_state )
	{
		case ActionProcesses::FollowingToTarget:
		{
			FollowingToTarget( dt );
			break;
		}
		case ActionProcesses::CirclingOverTarget:
		{
			CirclingOverTarget( dt );
			break;
		}
	}

	if ( m_timeInAction > m_flightTime )
	{
		m_state = ActionProcesses::ReturnToHangar;
	}
}


void Aircraft::FollowingToTarget( float dt )
{
	if ( CollisionAircraftAndTarget( *this, m_currentTarget ) )
	{
		m_state = ActionProcesses::CirclingOverTarget;
		return;
	}

	MoveTo( dt, m_currentTarget );
}


void Aircraft::CirclingOverTarget( float dt )
{
	TargetPoint pointAroundTarget{ m_currentTarget };
	pointAroundTarget.center = pointAroundTarget.center + pointAroundTarget.radius;
	pointAroundTarget.radius = params::aircraft::DISTANCE_FROM_CIRCLING_TARGET;
	pointAroundTarget.center.rotateRelativeToPoint( m_angleWhenCirclingOverTarget, m_currentTarget.center );

	if ( CollisionAircraftAndTarget( *this, pointAroundTarget ) )
	{
		m_angleWhenCirclingOverTarget += params::aircraft::ANGULAR_SPEED * dt;
	}

#ifdef DRAW_DEBUG
	drawDebug::DrawDebug::Instance()->addShape(
		std::make_unique<drawDebug::Circle>( pointAroundTarget.center, 0.05f, 16, 2.0f, drawDebug::GREEN ) );
#endif // defined(DRAW_DEBUG)

	MoveTo( dt, pointAroundTarget );
}


void Aircraft::ReturnToHangar( float dt )
{
	const auto landingTrajectory{ m_aircraftCarrier->getLandingTrajectory() };

	m_currentTarget = landingTrajectory[currentPointIndexAtLanding] ;

	if ( m_currentTarget.center == m_aircraftCarrier->getPosition() )
	{
		m_aircraftCarrier->addAircraftToLand();
		m_state = ActionProcesses::Landing;
		m_timeInAction = 0.0f;
		return;
	}

	MoveTo( dt, m_currentTarget );

	if ( CollisionAircraftAndTarget( *this, m_currentTarget ) )
	{
		--currentPointIndexAtLanding;
		clamp<int64_t>( currentPointIndexAtLanding, 0, landingTrajectory.size() - 1 );
	}
}


void Aircraft::Landing( float dt )
{
	const float acceleration{ -1.0f * params::ship::LINEAR_SPEED / m_takeOffTime };
	m_velocity += acceleration * dt;

	clamp<float>( m_velocity, 0.1f, params::ship::LINEAR_SPEED );

	MoveTo( dt, m_currentTarget );

	if (CollisionAircraftAndTarget( *this, m_currentTarget ) )
	{
		m_velocity = 0.0f;
		m_aircraftCarrier->parkInHangar();
	}
}


void Aircraft::MoveTo( float dt, TargetPoint const& target )
{
	auto direction{ target.center - m_position };
	direction.normalize();

	const auto cosRotationAngle{ dotProduct( m_forwardVector, direction ) };
	if ( isInRange( cosRotationAngle, -1.0f, 1.0f ) )
	{
		m_angle += !isNearlyEqual( std::acos( cosRotationAngle ), 0.0f )
			? getDirectionalCoefficientOfRotation( direction ) * params::aircraft::ANGULAR_SPEED * dt
			: 0.0f;
	}

	m_forwardVector = Vector2( std::cos( m_angle ), std::sin( m_angle ) );
	m_forwardVector.normalize();

#ifdef DRAW_DEBUG
	drawDebug::DrawDebug::Instance()->addShape(
		std::make_unique<drawDebug::Line>( m_position, 100 * m_forwardVector ) );
#endif // defined(DRAW_DEBUG)
}


int32_t Aircraft::getDirectionalCoefficientOfRotation( Vector2 const& direction ) const
{
	auto alpha{
		std::atan2( direction.y, direction.x ) - std::atan2( m_forwardVector.y, m_forwardVector.x )
	};
	if ( std::abs( alpha ) > PI )
	{
		alpha *= -1;
		alpha = 2 * PI - alpha;
	}
	
	const bool isRightTurn{ alpha < 0 || alpha > 2 * PI };
	return isRightTurn ? -1 : 1;
}
