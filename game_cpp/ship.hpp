#pragma once

#ifndef __SHIP_HPP__
#define __SHIP_HPP__


#include "../framework/scene.hpp"
#include "../framework/game.hpp"

#include "vector2.hpp"

//-------------------------------------------------------
//	Simple ship logic
//-------------------------------------------------------


class Ship
{
public:
	Ship();

	virtual void init();
	virtual void deinit();

	void keyPressed( int key );
	void keyReleased( int key );
	
	virtual void update( float dt );
	virtual void mouseClicked( Vector2 worldPosition, bool isLeftButton );

protected:
	scene::Mesh* m_mesh;
	Vector2 m_position;
	float m_angle;

	bool m_input[game::KEY_COUNT];
};


#endif // !defined(__SHIP_HPP__)