#include "FilterBar.h"

#include "UI/Style.h"

FilterBar::FilterBar( Vector2& _cursor_position, Vector2 _size )
{
	float search_width = 870.f;
	float button_width = 200.f;
	float filter_width = _size.x - ( search_width + UI::MARGIN + button_width + UI::MARGIN );
	m_search = SearchElement( _cursor_position, Vector2( search_width, _size.y ) );
	_cursor_position.x += search_width + UI::MARGIN; 
	m_filter = FilterElement( _cursor_position, Vector2( filter_width, _size.y ) );
	_cursor_position.x += filter_width + UI::MARGIN; 
	m_package_button = Button( "Package", _cursor_position, Vector2( button_width, _size.y ), FilterBar::packageAssets );

}

void FilterBar::update()
{
	m_search.update();
	m_filter.update();
	m_package_button.tick();
}

void FilterBar::draw( void )
{
	m_search.draw();
	m_filter.draw();
	m_package_button.draw();
}

void FilterBar::packageAssets( void )
{
}
