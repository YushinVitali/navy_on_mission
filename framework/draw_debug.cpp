#include "draw_debug.hpp"

#ifdef DRAW_DEBUG

#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "../framework/common_constants.hpp"


namespace drawDebug
{
	Line::Line( Vector2 const& point1, Vector2 const& point2, float thickness, Color const& color )
		: m_point1{ point1 }, m_point2{ point2 }
	{
		m_color = color;
		m_thickness = thickness;
	}


	void Line::draw() const
	{
		glLoadIdentity();
		glLineWidth( m_thickness );
		glBegin( GL_LINES );
			glColor3f( m_color.r, m_color.g, m_color.b );
			glVertex2f( m_point1.x, m_point1.y );
			glVertex2f( m_point2.x, m_point2.y );
		glEnd();
	}


	Circle::Circle( Vector2 const& center, float radius, size_t numSegments, float thickness, Color const& color )
		: m_center{ center }, m_radius{ radius }, m_numSegments{ numSegments }
	{
		m_color = color;
		m_thickness = thickness;
	}


	void Circle::draw() const
	{
		glLoadIdentity();
		glLineWidth( m_thickness );
		glBegin( GL_LINE_LOOP );
			glColor3f( m_color.r, m_color.g, m_color.b );
			for (size_t i = 0; i < m_numSegments; ++i)
			{
				const float theta{ 2.0f * PI * static_cast<float>(i) / static_cast<float>(m_numSegments) };
				const float x{ m_radius * std::cosf(theta) };
				const float y{ m_radius * std::sinf(theta) };
				glVertex2f( x + m_center.x, y + m_center.y );
			}
		glEnd();
	}


	DrawDebug* DrawDebug::m_instance{ nullptr };


	DrawDebug* DrawDebug::Instance()
	{
		if ( !m_instance )
		{
			m_instance = new DrawDebug();
		}
		return m_instance;
	}


	void DrawDebug::addShape( std::unique_ptr<Shape> shape )
	{
		m_shapes.emplace_back( std::move( shape ) );
	}


	void DrawDebug::draw()
	{
		for ( auto const& line : m_shapes )
		{
			line->draw();
		}

		m_shapes.clear();
	}
} // namespace drawDebug

#endif // defined(DRAW_DEBUG)