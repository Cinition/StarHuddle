#pragma once

#include <raylib.h>

namespace UIUtil
{
	extern void drawBackground( Vector2 _position, Vector2 _size, Color _color );
	extern void drawTextCentered( const char* _text, Vector2 _position, float _available_width, int _font_size, Color _color );
	extern void drawText( const char* _text, Vector2 _position, int _font_size, Color _color );
	extern void drawTexture( Vector2 _position, Vector2 _size, Texture2D _texture );
}
