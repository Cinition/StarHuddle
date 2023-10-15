#pragma once

#include "raylib.h"

#include <string>

class Button
{
public:

	typedef void ( *callback_function )( void );

	Button( void ) = default;
	Button( const std::string& _text, Vector2 & _cursor_position, Vector2 _size, callback_function _func );

	void tick( void );
	void draw( void );

private:

	void checkIfButtonPressed( Vector2 _cursor_position );
	bool isCursorInside( Vector2 _cursor_position );

	callback_function m_callback;
	std::string       m_text;
	Vector2           m_position;
	Vector2           m_size;
	bool              m_pressed = false;
	bool              m_hovered = false;

};
