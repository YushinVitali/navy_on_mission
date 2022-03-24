#pragma once

#ifndef __GAME_PARAMS_HPP__
#define __GAME_PARAMS_HPP__


//-------------------------------------------------------
//	game parameters
//-------------------------------------------------------

namespace params
{
	namespace ship
	{
		constexpr float LINEAR_SPEED = 0.5f;
		constexpr float ANGULAR_SPEED = 0.5f;
	}

	namespace aircraft
	{
		constexpr float LINEAR_SPEED = 2.f;
		constexpr float ANGULAR_SPEED = 2.5f;
		constexpr float FLIGHT_TIME = 30.0f;

		constexpr float DISTANCE_FROM_CIRCLING_TARGET = 0.2f;
	}

	namespace hangar
	{
		constexpr size_t HANGAR_CAPACITY = 5;
		constexpr float REFUELING_TIME = 5.0f;
	}
}


#endif // !defined(__GAME_PARAMS_HPP__)
