#pragma once

#include "raylib.h"

class Button
{
public:

	typedef void ( *callback_function )( void );

	Button( void ) = default;
	Button( callback_function _func );

	void tick( void );
	void draw( Vector2& _cursor_position, Vector2 _size );

private:

	void checkIfButtonPressed( Vector2 _cursor_position );
	bool isCursorInside( Vector2 _cursor_position );

	callback_function m_callback;
	Vector2 m_position = Vector2( 0.f, 0.f );
	Vector2 m_size = Vector2( 0.f, 0.f );
	Color m_normal_color;
	Color m_hover_color;
	Color m_selected_color;
	bool m_pressed = false;
	bool m_hovered = false;

};
