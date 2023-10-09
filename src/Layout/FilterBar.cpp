#include "FilterBar.h"

FilterBar::FilterBar( void )
{
	m_add_file_button = Button( FilterBar::addFile );
}

void FilterBar::update()
{
	m_add_file_button.tick();
}

void FilterBar::render( Vector2& _cursor_position )
{
	m_add_file_button.draw( _cursor_position, { 150, 50 } );
}

void FilterBar::addFile( void )
{
	return;
}
