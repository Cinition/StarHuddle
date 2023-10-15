#include "Button.h"

#include "raymath.h"

#include "UI/Style.h"

Button::Button( const std::string& _text, Vector2& _cursor_position, Vector2 _size, callback_function _func )
: m_text( _text )
, m_position( _cursor_position )
, m_size( _size )
, m_callback( _func )
{
	_cursor_position.y += _size.y;
}

void Button::tick(void)
{
	auto cursor_position = GetMousePosition();
	auto is_cursor_inside = isCursorInside(cursor_position);

	m_pressed = false;
	m_hovered = is_cursor_inside;

	if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
	{
		m_pressed = is_cursor_inside;
		if( m_pressed )
			m_callback();
	}
}

void Button::draw( void )
{
	auto bg_color = UI::PRIMARY;

	if( m_pressed )
	{
		auto pressed_color = ColorToHSV( bg_color );
		pressed_color.z += 0.25f;
		bg_color = ColorFromHSV( pressed_color.x, pressed_color.y, pressed_color.z );
	}
	else if( m_hovered )
	{
		auto hovered_color = ColorToHSV( bg_color );
		hovered_color.z += 0.15f;
		bg_color = ColorFromHSV( hovered_color.x, hovered_color.y, hovered_color.z );
	}

	RaylibRectangle rectangle;
	rectangle.x      = m_position.x;
	rectangle.y      = m_position.y;
	rectangle.width  = m_size.x;
	rectangle.height = m_size.y;

	DrawRectangleRounded( rectangle, 0.75f, 11, bg_color );

	int font_size = 15;
	RaylibDrawText( m_text.c_str(), m_position.x + ( m_size.x - MeasureText( m_text.c_str(), font_size ) ) / 2, m_position.y + ( m_size.y - font_size ) / 2, font_size, UI::TEXT_COLOR );
}

void Button::checkIfButtonPressed(Vector2 _cursor_position)
{
	if( !IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
		return;

	m_pressed = isCursorInside( _cursor_position );
}

bool Button::isCursorInside( Vector2 _cursor_position )
{
	auto min_position = m_position;
	auto max_position = Vector2( m_position.x + m_size.x, m_position.y + m_size.y );

	auto valid_min_position = ( _cursor_position.x > min_position.x && _cursor_position.x < max_position.x );
	auto valid_max_position = ( _cursor_position.y > min_position.y && _cursor_position.y < max_position.y );

	if( valid_min_position && valid_max_position )
		return true;
		
	return false;
}
