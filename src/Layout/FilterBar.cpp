#include "FilterBar.h"

FilterBar::FilterBar( Vector2& _cursor_pos )
{
	m_add_file_button = Button( _cursor_pos, Vector2( 80, 20 ), FilterBar::addFile );
	_cursor_pos = Vector2(_cursor_pos.x, _cursor_pos.y + 20.f + 15.f);
}

void FilterBar::update()
{
	m_add_file_button.tick();
}

void FilterBar::render()
{
	m_add_file_button.draw();
}

void FilterBar::addFile( void )
{
	
}
