#include "FilterElement.h"

#include "Utils/ElementHelper.h"

FilterElement::FilterElement( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	m_use_inner_margin = false;
}

void FilterElement::update( void )
{
	if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
		m_if_focused = ElementHelper::mouseInsideUIElement( *this );
}

void FilterElement::drawInner( Vector2 _cursor_positions )
{
	if( m_if_focused )
		drawFocused( _cursor_positions );
	else
		drawNotFocused( _cursor_positions );
}

void FilterElement::drawFocused( Vector2 _cursor_position )
{
}

void FilterElement::drawNotFocused( Vector2 _cursor_position )
{
}
