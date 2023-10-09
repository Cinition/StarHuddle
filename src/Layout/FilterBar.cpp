#include "FilterBar.h"

FilterBar::FilterBar( void )
{
	m_add_file_button = Button( FilterBar::addFile );
	m_bg_color = Color( 71, 71, 71, 255 );
}

void FilterBar::update()
{
	m_add_file_button.tick();
}

void FilterBar::render( Vector2& _cursor_position )
{
	m_add_file_button.draw( _cursor_position, { 150, 50 } );
	drawFilters( _cursor_position );
	drawGroups( _cursor_position );
}

void FilterBar::addFile( void )
{
	return;
}

void FilterBar::drawFilters(Vector2& _cursor_position)
{
	Rectangle rect;
	rect.x = _cursor_position.x;
	rect.y = _cursor_position.y;
	rect.width = 150;
	rect.height = 409;

	DrawRectangleRounded( rect, 0.3f, 7, m_bg_color );
	_cursor_position.y += 409 + 20.f;
}

void FilterBar::drawGroups(Vector2& _cursor_position)
{
	Rectangle rect;
	rect.x = _cursor_position.x;
	rect.y = _cursor_position.y;
	rect.width = 150;
	rect.height = 409;

	DrawRectangleRounded( rect, 0.3f, 7, m_bg_color );
	_cursor_position.y += 409 + 20.f;
}
