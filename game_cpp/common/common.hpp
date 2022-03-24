#pragma once

#ifndef __COMMON_HPP__
#define __COMMON_HPP__


bool isNearlyEqual( float x, float y, float epsilon = 0.0001f );


bool isInRange( float value, float min, float max );


template<typename T>
void clamp( T& value, T min, T max )
{
	if ( value < min )
	{
		value = min;
	}
	else if ( value > max )
	{
		value = max;
	}
}


#endif // !defined(__COMMON_HPP__)
