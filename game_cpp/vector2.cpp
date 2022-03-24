#include "vector2.hpp"

#include <cmath>

#include "common/common.hpp"


Vector2::Vector2() :
	x{ 0.f }, y{ 0.f }
{
}


Vector2::Vector2( float vx, float vy ) :
	x{ vx }, y{ vy }
{
}


Vector2::Vector2( Vector2 const& other ) :
	x{ other.x }, y{ other.y }
{
}


Vector2& Vector2::operator += ( float scalar )
{
	this->x += scalar;
	this->y += scalar;
	return *this;
}


Vector2& Vector2::operator += ( Vector2 const& value )
{
	this->x += value.x;
	this->y += value.y;
	return *this;
}


void Vector2::normalize()
{
	const auto length{ this->length() };
	if ( 0 == length ) {
		return;
	}
	const auto reverseLenght{ 1 / length };
	x *= reverseLenght;
	y *= reverseLenght;
}


float Vector2::length() const
{
	return std::sqrt( std::pow( x, 2 ) + std::pow( y, 2 ) );
}


void Vector2::rotate( float angle )
{
	const auto rotationVector{ Vector2{ std::cos( angle ), std::sin( angle ) } };
	rotate( rotationVector );
}


void Vector2::rotate( Vector2 const& rotationVector )
{
	auto oldX = x;
	auto oldY = y;

	x = oldX * rotationVector.x - oldY * rotationVector.y;
	y = oldX * rotationVector.y + oldY * rotationVector.x;
}


void Vector2::rotateRelativeToPoint( float angle, Vector2 const& center )
{
	const auto rotationVector{ Vector2{ std::cos( angle ), std::sin(angle ) } };
	rotateRelativeToPoint( rotationVector, center );
}


void Vector2::rotateRelativeToPoint( Vector2 const& rotationVector, Vector2 const& center )
{
	auto oldX = x;
	auto oldY = y;

	auto shiftX{ -1.0f * center.x * (rotationVector.x - 1.0f) + center.y * rotationVector.y };
	auto shiftY{ -1.0f * center.y * (rotationVector.x - 1.0f) - center.x * rotationVector.y };

	x = oldX * rotationVector.x - oldY * rotationVector.y + shiftX;
	y = oldX * rotationVector.y + oldY * rotationVector.x + shiftY;
}


Vector2 operator + ( Vector2 const& left, Vector2 const& right )
{
	return Vector2( left.x + right.x, left.y + right.y );
}


Vector2 operator + ( Vector2 const& v, float scalar )
{
	return Vector2( v.x + scalar, v.y + scalar );
}


Vector2 operator - ( Vector2 const& left, Vector2 const& right )
{
	return Vector2( left.x - right.x, left.y - right.y );
}


Vector2 operator * ( float left, Vector2 const& right )
{
	return Vector2( left * right.x, left * right.y );
}


bool operator == ( Vector2 const& v1, Vector2 const& v2 )
{
	return isNearlyEqual( v1.x, v2.x ) && isNearlyEqual( v1.y, v2.y );
}


bool operator != ( Vector2 const& v1, Vector2 const& v2 )
{
	return !isNearlyEqual( v1.x, v2.x ) ||  !isNearlyEqual( v1.y, v2.y );
}


float dotProduct( Vector2 const& v1, Vector2 const& v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}
