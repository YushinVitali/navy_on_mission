
#include <cassert>
#include <cmath>
#include <memory>

#include "../framework/scene.hpp"
#include "../framework/game.hpp"

#include "ship.hpp"
#include "vector2.hpp"
#include "aircraft_carrier.hpp"


//-------------------------------------------------------
//	game public interface
//-------------------------------------------------------

namespace game
{
	std::unique_ptr<Ship> ship{ std::make_unique<AircraftCarrier>() };


	void init()
	{
		ship->init();
	}


	void deinit()
	{
		ship->deinit();
	}


	void update( float dt )
	{
		ship->update( dt );
	}


	void keyPressed( int key )
	{
		ship->keyPressed( key );
	}


	void keyReleased( int key )
	{
		ship->keyReleased( key );
	}


	void mouseClicked( float x, float y, bool isLeftButton )
	{
		Vector2 worldPosition( x, y );
		scene::screenToWorld( &worldPosition.x, &worldPosition.y );
		ship->mouseClicked( worldPosition, isLeftButton );
	}
}

