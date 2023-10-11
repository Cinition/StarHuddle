#include "DetailBar.h"

DetailBar::DetailBar( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	m_export_button = Button( _cursor_position, Vector2( m_inner_size.x, 40.f ), DetailBar::exportFile );
}

void DetailBar::update(void)
{
}

void DetailBar::drawInner( Vector2 _cursor_position )
{
}

void DetailBar::exportFile( void )
{
}
