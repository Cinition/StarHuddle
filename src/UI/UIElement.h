#pragma once

#include "raylib.h"

#include <string>

class UIElement
{
public:

	UIElement( void ) = default;
	UIElement( Vector2& _cursor_position, Vector2 _size );

	void draw( void );

	virtual void drawChildren( Vector2 _cursor_position ) = 0;
	virtual std::string getTitle( void ) { return ""; }

protected:

	Vector2 m_position;
	Vector2 m_size;
	float   m_roundness = 0.25f;
};
