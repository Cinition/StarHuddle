#include "AssetGrid.h"

#include "UI/Style.h"

constexpr Vector2 ASSET_FRAME_SIZE = Vector2( 123, 123 );

AssetGrid::AssetGrid(Vector2& _cursor_position, Vector2 _size)
: UIElement( _cursor_position, _size )
{
	m_roundness = 0.05f;
}

void AssetGrid::drawChildren(void)
{
}

void AssetGrid::drawAsset( Vector2& _cursor_position, Vector2 _cutoff )
{
	auto cursor_position = Vector2( _cursor_position.x += 20, _cursor_position.y + 20 );
	DrawRectangle( cursor_position.x, cursor_position.y, ASSET_FRAME_SIZE.x, ASSET_FRAME_SIZE.y, Color( 217, 217, 217, 255 ) );

	_cursor_position.x += ASSET_FRAME_SIZE.x;
}
