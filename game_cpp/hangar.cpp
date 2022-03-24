#include "hangar.hpp"

#include <iostream>

#include "aircraft_carrier.hpp"

#include "common/common.hpp"


void Hangar::init( AircraftCarrier* aircraftCarrier )
{
	if (aircraftCarrier)
	{
		m_aircraftCarrier = aircraftCarrier;
	}
}


void Hangar::deinit()
{
	for (auto& aircraft : m_aircraftOnFlight)
	{
		aircraft.deinit();
	}

	m_aircraftOnFlight.clear();
	m_aircraftCarrier = nullptr;

	m_counterForParking = 0;
	m_refuelingTime = 0.0f;
	m_counterOnRefueling = 0;
	m_counterToLanding = 0;
}


void Hangar::update( float dt )
{
	if ( m_counterOnRefueling != 0 )
	{
		m_refuelingTime += dt;
	}

	if ( m_refuelingTime >= m_refuelingTimeRequired )
	{
		--m_counterOnRefueling;
		m_refuelingTime = 0.0f;
	}

	park();

	for ( auto& aircraft : m_aircraftOnFlight )
	{
		aircraft.update( dt );
	}
}


void Hangar::sendToFlight()
{
	if( !isReadyAircraft() || !m_aircraftCarrier )
	{
		return;
	}

	Aircraft aircraft;
	aircraft.init( m_aircraftCarrier, m_aircraftCarrier->getPosition(), m_aircraftCarrier->getForwardVector() );

	m_aircraftOnFlight.emplace_back( std::move( aircraft ) );

	m_aircraftCarrier->OccupyRunwayForTakeoff();
}


void Hangar::addToParkingQueue()
{
	++m_counterForParking;
}


void Hangar::addAircraftToLand()
{
	++m_counterToLanding;
}


size_t Hangar::getNumberAircraftToLand() const
{
	return m_counterToLanding;
}


void Hangar::park()
{
	for( ; m_counterForParking != 0; --m_counterForParking )
	{
		m_aircraftOnFlight.front().deinit();
		m_aircraftOnFlight.erase( m_aircraftOnFlight.begin() );

		--m_counterToLanding;
		++m_counterOnRefueling;
	}
}


bool Hangar::isReadyAircraft() const
{
	return m_aircraftOnFlight.size() < m_capacity 
		&& m_capacity - m_aircraftOnFlight.size() > m_counterOnRefueling;
}