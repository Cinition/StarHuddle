#include "FilterBar.h"

#include "UI/Style.h"

FilterBar::FilterBar( Vector2& _cursor_position, Vector2 _size )
{
	m_add_file_button = Button( _cursor_position, Vector2( _size.x, 50 ), FilterBar::addFile );
	_cursor_position.y += UI::MARGIN;
	m_filters = FilterElement( _cursor_position, Vector2( _size.x, 400 ) );
	_cursor_position.y += UI::MARGIN;
	m_groups = GroupElement( _cursor_position, Vector2( _size.x, _size.y - 400 - 50 - ( UI::MARGIN * 2 ) ) );

	// Reset Cursor
	_cursor_position.x += _size.x + UI::MARGIN;
	_cursor_position.y = UI::MARGIN;
}

void FilterBar::update()
{
	m_add_file_button.tick();
}

void FilterBar::draw( void )
{
	m_add_file_button.draw();
	m_filters.draw();
	m_groups.draw();
}

void FilterBar::addFile( void )
{
	return;
}
