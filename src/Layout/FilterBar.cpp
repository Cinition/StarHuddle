#include "FilterBar.h"

#include "UI/Style.h"

FilterBar::FilterBar( Vector2& _cursor_position, Vector2 _size )
{
	float search_width = 870.f;
	m_search = SearchElement( _cursor_position, Vector2( search_width, _size.y ) );
	_cursor_position.x += search_width + UI::MARGIN; 
	m_filter = FilterElement( _cursor_position, Vector2( _size.x - search_width - UI::MARGIN, _size.y ) );
}

void FilterBar::update()
{
}

void FilterBar::draw( void )
{
	m_search.draw();
	m_filter.draw();
}
