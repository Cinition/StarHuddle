#include "Input.h"

#include "UI/Style.h"
#include "Util/UIUtil.h"
#include "Util/InputUtil.h"

Input::Input( const Vector2& _position, const Vector2& _size )
: UIElement( _position, _size )
, m_bg_color( UI::GRADIENT1 )
{
}

void Input::update( const float /*_tick*/ )
{
	if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
		m_focused = InputUtil::isMouseInside( m_position, Vector2Add( m_position, m_size ) );

	if( !m_focused )
		return;

	if( handleSpecialInput() )
		return;

	// Insert key strokes into the text variable
	int keyboard_key = GetCharPressed();
	while( keyboard_key > 0 )
	{
		// Only allow keys in range [32..125]
		if( ( keyboard_key >= 32 ) && ( keyboard_key <= 125 ) )
			m_input_text.insert( m_input_text.end(), ( char )keyboard_key );

		keyboard_key = GetCharPressed(); // Check next character in the queue
	}
}

void Input::draw( void )
{
	UIUtil::drawBackground( m_position, m_size, m_bg_color );

	auto inner_position = Vector2Add( m_position, Vector2( UI::MARGIN, UI::MARGIN ) );
	UIUtil::drawText( m_input_text.c_str(), inner_position, 16, UI::TEXT_COLOR );
	drawInputCursor( inner_position );
}

bool Input::handleSpecialInput( void )
{
	if( IsKeyDown( KEY_LEFT_CONTROL ) && IsKeyPressed( KEY_BACKSPACE ) )
	{
		m_input_text.clear();
	}
	else if( IsKeyPressed( KEY_BACKSPACE ) )
	{
		if( m_input_cursor > 0 )
			m_input_text.erase( static_cast< size_t >( m_input_cursor - 1 ) );
	}
	else if( IsKeyPressed( KEY_LEFT ) )
	{
		if( m_input_cursor > 0 )
			m_input_cursor -= 1;
	}
	else if( IsKeyPressed( KEY_RIGHT ) )
	{
		if( m_input_text.size() < m_input_cursor )
			m_input_cursor += 1;
	}

	return false;
}

void Input::drawInputCursor( Vector2 _inner_position )
{
	auto cursor_x        = static_cast< float >( MeasureText( std::string( m_input_text.c_str(), static_cast< size_t >( m_input_cursor ) ).c_str(), 16 ) );
	auto cursor_position = Vector2Add( _inner_position, Vector2( cursor_x, -2 ) );

	DrawRectangle( static_cast< int >( cursor_position.x ), static_cast< int >( cursor_position.y ), 2, 20, UI::TEXT_COLOR );
}
