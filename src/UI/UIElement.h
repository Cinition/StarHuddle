#pragma once

#include "raylib.h"

#include <string>

class UIElement
{
public:

	UIElement( void ) = default;
	UIElement( Vector2& _cursor_position, Vector2 _size );

	void draw( void );

	virtual void drawChildren( void ) = 0;
	virtual std::string getTitle( void ) { return ""; }

protected:

	float m_roundness = 0.25f;

private:

	Vector2 m_position;
	Vector2 m_size;
};
