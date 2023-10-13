#pragma once

#include "raylib.h"

class UIElement
{

public:

	UIElement( void ) = default;
	UIElement( Vector2& _cursor_position, Vector2 _size );

	void draw( void );

	virtual void drawInner( Vector2 _cursor_position ) = 0;

	const Vector2& getPosition() const { return m_position; }
	const Vector2& getSize()     const { return m_size; }

protected:

	Vector2 m_position;
	Vector2 m_size;
	Vector2 m_inner_size;
	float   m_roundness        = 20.f;
	bool    m_use_inner_margin = true;
	bool    m_if_focused       = false;
};
