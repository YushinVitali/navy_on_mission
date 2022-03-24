#pragma once

#ifndef __COLLISION_HPP__
#define __COLLISION_HPP__


class Aircraft;
struct TargetPoint;


bool CollisionAircraftAndTarget( Aircraft const& aircraft, TargetPoint const& target );


#endif // !defined(__COLLISION_HPP__)
