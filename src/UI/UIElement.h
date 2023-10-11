#pragma once

#include "raylib.h"

#include <string>

class UIElement
{
public:

	UIElement( void ) = default;
	UIElement( Vector2& _cursor_position, Vector2 _size );

	void draw( void );

	virtual void        drawInner( Vector2 _cursor_position ) = 0;
	virtual std::string getTitle( void ) { return ""; }

protected:

	Vector2 m_position;
	Vector2 m_size;
	Vector2 m_inner_size;
	float   m_roundness        = 10.f;
	bool    m_use_inner_margin = true;
};
