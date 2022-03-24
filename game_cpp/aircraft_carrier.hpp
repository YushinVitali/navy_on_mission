#pragma once

#ifndef __AIRCRAFT_CARRIER_HPP__
#define __AIRCRAFT_CARRIER_HPP__


#include <vector>

#include "ship.hpp"
#include "hangar.hpp"


class Vector2;
class Aircraft;
struct TargetPoint;


class AircraftCarrier : public Ship
{
public:
	virtual void init() override;
	virtual void deinit() override;
	virtual void update(float dt) override;
	virtual void mouseClicked( Vector2 worldPosition, bool isLeftButton ) override;
	
	/// @brief Add an airplane to the hangar parking queue.
	void parkInHangar();

	/// @brief Adds a value to the counter for the ability to block the landing strip.
	void addAircraftToLand();

	void OccupyRunwayForTakeoff();
	void ReportRunwayClearance();

	Vector2 getPosition() const;
	Vector2 getForwardVector() const;

	/// @brief Get the mission objective.
	TargetPoint getTarget() const;

	std::vector<TargetPoint> const& getLandingTrajectory();

private:
	bool isRunwayBusy() const;

	void FillLandingTrajectory();
	void UpdateLandingTrajectory();

private:
	Hangar m_hangar;

	/// @brief Points describing the aircraft landing trajectory.
	std::vector<TargetPoint> m_landingTrajectory;
	/// @brief Distance between landing points to build a trajectory.
	const float m_distanceBetweenLandingPoints{ 1.0f };

	Vector2 m_forwardVector{ 1.0f, 0.0f };

	/// @brief Mission Objective.
	TargetPoint m_target{ { 0.0f, 0.0f }, 0.5f };

	/// @brief Indicates whether the runway is occupied by the aircraft taking off.
	bool m_isAircraftTakingOff{ false };
};


#endif // !defined(__AIRCRAFT_CARRIER_HPP__)
