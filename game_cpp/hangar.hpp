#pragma once

#ifndef __HANGAR_HPP__
#define __HANGAR_HPP__


#include <list>

#include "game_params.hpp"
#include "aircraft.hpp"


class AircraftCarrier;


class Hangar
{
public:
	void init( AircraftCarrier* aircraftCarrier );
	void deinit();
	void update( float dt );

	void sendToFlight();

	/// @brief Add a counter to the number of aircraft arriving.
	/// @details Since we always know that the first departed arrives,
	///			 aircraft arrivals are based on counters, not aircraft IDs.
	void addToParkingQueue();
	
	/// @brief Add a counter for the number of planes in the landing process.
	void addAircraftToLand();
	size_t getNumberAircraftToLand() const;

	bool isReadyAircraft() const;

private:
	/// @brief Remove incoming aircrafts.
	void park();

private:
	/// @brief HeadquartersHeadquarters
	AircraftCarrier* m_aircraftCarrier{ nullptr };

	std::list<Aircraft> m_aircraftOnFlight;

	const size_t m_capacity{ params::hangar::HANGAR_CAPACITY };

	const float m_refuelingTimeRequired{ params::hangar::REFUELING_TIME };
	float m_refuelingTime{ 0.0f };

	/// @brief Number of planes in the parking process.
	size_t m_counterForParking{ 0 };
	/// @brief Number of planes in the process of landing.
	size_t m_counterToLanding{ 0 };
	/// @brief Number of planes in the refueling process.
	size_t m_counterOnRefueling{ 0 };
};


#endif // !defined(__HANGAR_HPP__)
