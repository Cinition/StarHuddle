#include "Button.h"

Button::Button( Vector2& _cursor_position, Vector2 _size, callback_function _func )
: m_position( _cursor_position )
, m_size( _size )
, m_callback( _func )
, m_normal_color( Color( 34, 189, 106, 255 ) )
, m_hover_color( Color( 40, 227, 127, 255 ) )
, m_selected_color( Color( 24, 138, 77, 255 ) )
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
	auto bg_color = m_normal_color;

	if( m_pressed )      bg_color = m_selected_color;
	else if( m_hovered ) bg_color = m_hover_color;

	Rectangle rectangle;
	rectangle.x = m_position.x;
	rectangle.y = m_position.y;
	rectangle.width = m_size.x;
	rectangle.height = m_size.y;

	DrawRectangleRounded( rectangle, 0.75f, 11, bg_color );
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
