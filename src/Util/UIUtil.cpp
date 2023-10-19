#include "UIUtil.h"

#include "UI/Style.h"

#include <raymath.h>

#include <string>
#include <vector>

void UIUtil::drawBackground( Vector2 _position, Vector2 _size, Color _color )
{
	RaylibRectangle rectangle;
	rectangle.x      = _position.x;
	rectangle.y      = _position.y;
	rectangle.width  = _size.x;
	rectangle.height = _size.y;

	DrawRectangleRounded( rectangle, UI::CORNER_ROUNDNESS / fminf( _size.x, _size.y ), 11, _color );
}

void UIUtil::drawTextCentered( const char* _text, Vector2 _position, float _available_width, int _font_size, Color _color )
{
	int         begin_column_pos  = 0;
	std::string text              = std::string( _text );
	int         char_size         = static_cast< int >( MeasureText( _text, _font_size ) / floorf( static_cast< float >( text.size() ) ) );
	int         text_column_count = static_cast< int >( _available_width / char_size );
	std::vector< std::string > text_columns;
	for( int i = 0; i <= text.size(); i++ )
	{
		if( i > 0 && i % text_column_count == 0 )
		{
			text_columns.push_back( { text, static_cast< size_t >( begin_column_pos ), static_cast< size_t >( i ) } );
			begin_column_pos = i;
			continue;
		}
		if( static_cast< size_t >( i ) == text.size() )
			text_columns.push_back( { text, static_cast< size_t >( begin_column_pos ), static_cast< size_t >( i ) } );
	}

	Vector2 column_position = _position;
	for( auto& column : text_columns )
	{
		float text_x = column_position.x + ( _available_width - MeasureText( column.c_str(), _font_size ) ) / 2;
		UIUtil::drawText( column.c_str(), Vector2( text_x, column_position.y ), _font_size, _color );
		column_position.y += _font_size;
	}
}

void UIUtil::drawText( const char* _text, Vector2 _position, int _font_size, Color _color )
{
	RaylibDrawText( _text, static_cast< int >( _position.x ), static_cast< int >( _position.y ), _font_size, _color );
}

void UIUtil::drawTexture( Vector2 _position, Vector2 _size, Texture2D _texture, bool _invert )
{
	RaylibRectangle src_rect;
	src_rect.x      = 0.f;
	src_rect.y      = 0.f;
	src_rect.height = static_cast< float >( ( _invert ? -_texture.height : _texture.height ) );
	src_rect.width  = static_cast< float >( _texture.width );

	RaylibRectangle dst_rect;
	dst_rect.x      = _position.x;
	dst_rect.y      = _position.y;
	dst_rect.height = _size.y;
	dst_rect.width  = _size.x;

	DrawTexturePro( _texture, src_rect, dst_rect, { 0.f, 0.f }, 0, WHITE );
}
