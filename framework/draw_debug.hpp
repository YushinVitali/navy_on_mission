#pragma once

/// To display debugging information.
//#define DRAW_DEBUG

#ifdef DRAW_DEBUG

#ifndef __DRAW_DEBUG_HPP__
#define __DRAW_DEBUG_HPP__


#include <vector>
#include <memory>

#include "../game_cpp/vector2.hpp"


namespace drawDebug
{
	struct Color
	{
		float r, g, b;
	};

	constexpr Color RED{ 255.0f, 0.0f, 0.0f };
	constexpr Color GREEN{ 0.0f, 255.0f, 0.0f };
	constexpr Color BLUE{ 0.0f, 0.0f, 255.0f };

	constexpr Color WHITE{ 255.0f, 255.0f, 255.0f };
	constexpr Color BLACK{ 0.0f, 0.0f, 0.0f };


	class Shape
	{
	public:
		virtual void draw() const = 0;

	protected:
		Color m_color{ RED };
		float m_thickness{ 1.0f };
	};


	class Line : public Shape
	{
	public:
		Line( Vector2 const& point1, Vector2 const& point2, float thickness = 1.0f, Color const& color = RED );
		virtual void draw() const;

	private:
		Vector2 m_point1;
		Vector2 m_point2;
	};


	class Circle : public Shape
	{
	public:
		Circle( Vector2 const& center, float radius = 0.1f, size_t numSegments = 16, float thickness = 1.0f, Color const& color = RED );
		virtual void draw() const;

	private:
		Vector2 m_center;
		float m_radius;

		size_t m_numSegments;
	};


	class DrawDebug
	{
	public:
		static DrawDebug* Instance();

		void addShape( std::unique_ptr<Shape> shape );

		void draw();

	private:
		static DrawDebug* m_instance;

		std::vector<std::unique_ptr<Shape>> m_shapes;
	};
}


#endif // !defined(__DRAW_DEBUG_HPP__)

#endif // defined(DRAW_DEBUG)