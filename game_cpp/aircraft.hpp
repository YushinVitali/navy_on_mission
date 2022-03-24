#pragma once

#ifndef __AIRCRAFT_HPP__
#define __AIRCRAFT_HPP__


#include <memory>

#include "../framework/scene.hpp"

#include "game_params.hpp"

#include "common/target_point.hpp"


class AircraftCarrier;
class Vector2;


/// @brief Possible aircraft actions.
enum class ActionProcesses
{
	TakingOff,
	FollowingToTarget,
	CirclingOverTarget,
	ReturnToHangar,
	Landing,
};


class Aircraft
{
public:
	void init( AircraftCarrier* aircraftCarrier, Vector2 const& startPosition, Vector2 const& forwardVector );
	void deinit();
	void update( float dt );

	Vector2 getForwardVector() const;
	Vector2 getPosition() const;

private:
	void Takeoff( float dt );
	
	void OnMission( float dt );
	void FollowingToTarget( float dt );
	void CirclingOverTarget( float dt );
	
	void ReturnToHangar( float dt );
	void Landing( float dt );

	void MoveTo( float dt, TargetPoint const& target );

	/// @retval 1	if turning left.
	/// @retval -1	if turning right.
	int32_t getDirectionalCoefficientOfRotation( Vector2 const& direction ) const;

private:
	scene::Mesh* m_mesh{ nullptr };
	Vector2 m_position;
	float m_angle{ 0.0f };

	/// @brief Headquarters.
	AircraftCarrier* m_aircraftCarrier{ nullptr };

	/// @brief Amount of time allowed for takeoff.
	const float m_takeOffTime{ 5.0f };
	const float m_flightTime{ params::aircraft::FLIGHT_TIME };

	float m_velocity{ 0.0f };
	Vector2 m_forwardVector{ 1.0f, 0.0f };

	ActionProcesses m_state{ ActionProcesses::TakingOff };
	float m_timeInAction{ 0.0f };

	/// @brief Current target to which the aircraft is heading.
	TargetPoint m_currentTarget;

	float m_angleWhenCirclingOverTarget;

	int64_t currentPointIndexAtLanding;
};


#endif // !defined(__AIRCRAFT_HPP__)
