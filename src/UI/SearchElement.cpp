#include "SearchElement.h"

#include "Utils/ElementHelper.h"

SearchElement::SearchElement( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	m_use_inner_margin = false;
}

void SearchElement::update( void )
{
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
	// draw blinker
}

void SearchElement::drawNotFocused( Vector2 _cursor_position )
{
	// draw search icon
	// draw text "Search for any Asset"
}
