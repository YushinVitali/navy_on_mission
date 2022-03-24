#include "aircraft_carrier.hpp"

#include <cmath>
#include <cassert>

#include "../framework/draw_debug.hpp"

#include "aircraft.hpp"
#include "vector2.hpp"

#include "common/target_point.hpp"


void AircraftCarrier::init()
{
	Ship::init();

	m_hangar.init( this );

	FillLandingTrajectory();

	assert( ( !m_landingTrajectory.empty() ) && "There is no landing trajectory!" );
}


void AircraftCarrier::deinit()
{
	m_isAircraftTakingOff = false;
	m_landingTrajectory.clear();

	m_hangar.deinit();

	Ship::deinit();
}


void AircraftCarrier::update( float dt )
{
	// If the runway is busy landing or taking off an aircraft,
	// the aircraft carrier does not move.
	isRunwayBusy()
		? scene::placeMesh( m_mesh, m_position.x, m_position.y, m_angle )
		: Ship::update( dt );

	m_hangar.update( dt );

	m_forwardVector = Vector2( std::cos( m_angle ), std::sin( m_angle ) );
	UpdateLandingTrajectory();

#ifdef DRAW_DEBUG
	for ( const auto& point : m_landingTrajectory )
	{
		drawDebug::DrawDebug::Instance()->addShape(
			std::make_unique<drawDebug::Circle>( point.center ) );
	}
#endif // defined(DRAW_DEBUG)
}

void AircraftCarrier::mouseClicked( Vector2 worldPosition, bool isLeftButton )
{
	if ( isLeftButton )
	{
		m_target.center = worldPosition;
		scene::placeGoalMarker( m_target.center.x, m_target.center.y );
		return;
	}

	if(!isRunwayBusy())
	{
		m_hangar.sendToFlight();
	}
}


void AircraftCarrier::parkInHangar()
{
	m_hangar.addToParkingQueue();
}


void AircraftCarrier::addAircraftToLand()
{
	m_hangar.addAircraftToLand();
}


void AircraftCarrier::OccupyRunwayForTakeoff()
{
	m_isAircraftTakingOff = true;
}


void AircraftCarrier::ReportRunwayClearance()
{
	m_isAircraftTakingOff = false;
}


Vector2 AircraftCarrier::getPosition() const
{
	return m_position;
}


Vector2 AircraftCarrier::getForwardVector() const
{
	return m_forwardVector;
}


TargetPoint AircraftCarrier::getTarget() const
{
	return m_target;
}


std::vector<TargetPoint> const& AircraftCarrier::getLandingTrajectory()
{
	return m_landingTrajectory;
}


bool AircraftCarrier::isRunwayBusy() const
{
	bool isAircraftLanding{ m_hangar.getNumberAircraftToLand() > 0 };
	return m_isAircraftTakingOff || isAircraftLanding;
}


void AircraftCarrier::FillLandingTrajectory()
{
	const size_t numberLandingPoints{ 3 };
	for ( size_t i = 0; i < numberLandingPoints; ++i )
	{
		const Vector2 point{ m_position + i * m_distanceBetweenLandingPoints * m_forwardVector };
		m_landingTrajectory.emplace_back( point );
	}
}


void AircraftCarrier::UpdateLandingTrajectory()
{
	for ( size_t i = 0; i < m_landingTrajectory.size(); ++i )
	{
		m_landingTrajectory[i].center = m_position + i * m_distanceBetweenLandingPoints * m_forwardVector;
	}
}