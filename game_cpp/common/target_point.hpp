#pragma once

#ifndef __TARGET_POINT_HPP__
#define __TARGET_POINT_HPP__

#include "../vector2.hpp"


struct TargetPoint
{
	TargetPoint() = default;
	TargetPoint( Vector2 const& point, float r = 0.1f );

	Vector2 center{ 0.0f, 0.0f };
	float radius{ 0.1f };
};


bool operator == ( TargetPoint const& target1, TargetPoint const& target2 );
bool operator != ( TargetPoint const& target1, TargetPoint const& target2 );


#endif // !defined(__TARGET_POINT_HPP__)