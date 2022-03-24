#include "../game_cpp/ship.hpp"

#include <cassert>
#include <cmath>

#include "vector2.hpp"
#include "game_params.hpp"


Ship::Ship() :
	m_mesh(nullptr)
{
}


void Ship::init()
{
	assert( !m_mesh );
	m_mesh = scene::createShipMesh();
	m_position = Vector2( 0.f, 0.f );
	m_angle = 0.f;

	for (bool& key : m_input)
	{
		key = false;
	}
}


void Ship::deinit()
{
	scene::destroyMesh( m_mesh );
	m_mesh = nullptr;
}


void Ship::update( float dt )
{
	float linearSpeed = 0.f;
	float angularSpeed = 0.f;

	if ( m_input[game::KEY_FORWARD] )
	{
		linearSpeed = params::ship::LINEAR_SPEED;
	}
	else if ( m_input[game::KEY_BACKWARD] )
	{
		linearSpeed = -params::ship::LINEAR_SPEED;
	}

	if ( m_input[game::KEY_LEFT] && linearSpeed != 0.f )
	{
		angularSpeed = params::ship::ANGULAR_SPEED;
	}
	else if ( m_input[game::KEY_RIGHT] && linearSpeed != 0.f )
	{
		angularSpeed = -params::ship::ANGULAR_SPEED;
	}

	m_angle = m_angle + angularSpeed * dt;
	m_position = m_position + linearSpeed * dt * Vector2( std::cos( m_angle ), std::sin( m_angle ) );
	scene::placeMesh(m_mesh, m_position.x, m_position.y, m_angle);
}


void Ship::keyPressed( int key )
{
	assert( key >= 0 && key < game::KEY_COUNT );
	m_input[key] = true;
}


void Ship::keyReleased( int key )
{
	assert( key >= 0 && key < game::KEY_COUNT );
	m_input[key] = false;
}


void Ship::mouseClicked( Vector2 worldPosition, bool isLeftButton )
{
	if (isLeftButton)
	{
		scene::placeGoalMarker(worldPosition.x, worldPosition.y);
	}
}