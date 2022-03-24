#include "common.hpp"

#include <cmath>


bool isNearlyEqual( float x, float y, float epsilon )
{
	return std::fabs( x - y ) < epsilon;
}


bool isInRange( float value, float min, float max )
{
	return ( min <= value && value <= max );
}
