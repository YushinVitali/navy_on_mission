#pragma once

#ifndef __VECTOR2_HPP__
#define __VECTOR2_HPP__


//-------------------------------------------------------
//	Basic Vector2 class
//-------------------------------------------------------

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2( float vx, float vy );
	Vector2( Vector2 const& other );

	Vector2& operator += ( float scalar );
	Vector2& operator += ( Vector2 const& value );

	void normalize();
	float length() const;

	void rotate( float angle );
	void rotate( Vector2 const& rotationVector );
	void rotateRelativeToPoint( float angle , Vector2 const& center );
	void rotateRelativeToPoint( Vector2 const& rotationVector, Vector2 const& center );
};

Vector2 operator + ( Vector2 const& left, Vector2 const& right );
Vector2 operator + ( Vector2 const& v, float scalar );
Vector2 operator - ( Vector2 const& left, Vector2 const& right );
Vector2 operator * ( float left, Vector2 const& right );

bool operator == ( Vector2 const& v1, Vector2 const& v2 );
bool operator != ( Vector2 const& v1, Vector2 const& v2 );

float dotProduct( Vector2 const& v1, Vector2 const& v2 );


#endif // !defined(__VECTOR2_HPP__)