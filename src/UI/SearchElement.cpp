#include "SearchElement.h"

#include "Utils/ElementHelper.h"
#include "UI/Style.h"

SearchElement::SearchElement( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	m_use_inner_margin = false;
}

void SearchElement::update( void )
{
	if( m_if_focused )
	{
		int key = GetCharPressed();

		while( key > 0 )
		{
			// NOTE: Only allow keys in range [32..125]
			if( ( key >= 32 ) && ( key <= 125 ) )
			{
				m_input.insert( m_input.end(), ( char )key );
			}

			key = GetCharPressed(); // Check next character in the queue
		}

		if( IsKeyDown( KEY_LEFT_CONTROL ) && IsKeyPressed( KEY_BACKSPACE ) )
			m_input.clear();
		else if( IsKeyPressed( KEY_BACKSPACE ) )
			m_input.erase( m_input.end() - 1 );
	}

	if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
		m_if_focused = ElementHelper::mouseInsideUIElement( *this );
}

void SearchElement::drawInner( Vector2 _cursor_positions )
{
	if( m_if_focused )
		drawFocused( _cursor_positions );
	else
		drawNotFocused( _cursor_positions );
}

void SearchElement::drawFocused( Vector2 _cursor_position )
{
	// draw search icon
	// draw inputed text
	auto    font_size = 16;
	Vector2 text_pos  = Vector2( _cursor_position.x + ( UI::MARGIN / 2 ), _cursor_position.y + ( UI::MARGIN / 2 ) + ( 16 / 2 ) );
	RaylibDrawText( m_input.c_str(), text_pos.x, text_pos.y, font_size, UI::TEXT_COLOR );
	// draw blinker
}

void SearchElement::drawNotFocused( Vector2 _cursor_position )
{
	// draw search icon
	auto    font_size = 16;
	Vector2 text_pos  = Vector2( _cursor_position.x + ( UI::MARGIN / 2 ), _cursor_position.y + ( UI::MARGIN / 2 ) + ( 16 / 2 ) );
	RaylibDrawText( "Search for any Asset", text_pos.x, text_pos.y, font_size, UI::TEXT_COLOR );
}
