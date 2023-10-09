#include "AssetGrid.h"

AssetGrid::AssetGrid(void)
{
	m_bg_color = Color( 71, 71, 71, 255 );
}

void AssetGrid::update()
{
}

void AssetGrid::render(Vector2& _cursor_position)
{
	drawBG( _cursor_position );

	auto cursor_position = Vector2( _cursor_position.x + 20, _cursor_position.y + 20 );
	DrawRectangle( static_cast< int >( cursor_position.x ), static_cast< int >( cursor_position.y ), 100, 100, Color( 217, 217, 217, 255 ) );
}

void AssetGrid::drawBG(Vector2 _cursor_position)
{
	Rectangle bg_rect;
	bg_rect.x = _cursor_position.x;
	bg_rect.y = _cursor_position.y;
	bg_rect.width = 1305;
	bg_rect.height = 910;

	DrawRectangleRounded( bg_rect, 0.05f, 7, m_bg_color );
}
