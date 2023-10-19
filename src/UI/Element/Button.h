#pragma once

#include "UI/UIElement.h"

#include <raylib.h>

#include <string>

class Button : public UIElement
{
public:
	typedef void ( *callback_function )( void );

	Button( const std::string& _text, const Vector2& _position, const Vector2& _size, callback_function _func ); // Text Button
	Button( Texture2D _icon, Vector2 _icon_size, const Vector2& _position, const Vector2& _size, callback_function _func ); // Icon Button

	void update( const float _tick ) override;
	void draw  ( void ) override;

private:

	callback_function m_callback;
	Color             m_bg_color;
	Texture2D         m_icon;
	Vector2           m_icon_size;
	std::string       m_text     = "";
	bool              m_pressed  = false;
	bool              m_hovered  = false;

};
