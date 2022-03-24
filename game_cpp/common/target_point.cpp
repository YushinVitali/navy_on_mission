#include "target_point.hpp"

#include "common.hpp"

TargetPoint::TargetPoint(Vector2 const& point, float r)
	: center{ point }, radius{ r }
{
}


bool operator == ( TargetPoint const& target1, TargetPoint const& target2 )
{
	return target1.center == target2.center && isNearlyEqual(target1.radius, target2.radius);
}


bool operator != ( TargetPoint const& target1, TargetPoint const& target2 )
{
	return target1.center != target2.center || !isNearlyEqual(target1.radius, target2.radius);;
}