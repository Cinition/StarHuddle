#pragma once

#include "UI/UIElement.h"

#include <raylib.h>

#include <string>

class Input : public UIElement
{
public:

	Input( const Vector2& _cursor_position, const Vector2& _size );

	void update( const float _tick ) override;
	void draw  ( void ) override;

private:

	bool        handleSpecialInput( void );
	void        drawInputCursor( Vector2 _inner_position );

	Color       m_bg_color;
	Texture2D   m_search_icon;
	Vector2     m_search_icon_size = { 22.5f, 22.5f };
	std::string m_input_text       = "";
	uint32_t    m_input_cursor     = 0;
	bool        m_focused          = false;

};
