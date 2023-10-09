#include "AssetGrid.h"

constexpr Vector2 ASSET_GRID_SIZE = Vector2( 1305, 910 );
constexpr Vector2 ASSET_FRAME_SIZE = Vector2( 123, 123 );

AssetGrid::AssetGrid( void )
{
	m_bg_color = Color( 71, 71, 71, 255 );
}

void AssetGrid::update( void )
{
}

void AssetGrid::render( Vector2& _cursor_position )
{
	auto reset_cursor_pos = _cursor_position;
	auto total_grid_size = Vector2( ASSET_GRID_SIZE.x + _cursor_position.x, ASSET_GRID_SIZE.y + _cursor_position.y );
	drawBG( _cursor_position );

	for( int i = 0; i < 30; i += 1 )
	{
		if( ( _cursor_position.x + ASSET_FRAME_SIZE.x ) > total_grid_size.x )
		{
			_cursor_position.x = reset_cursor_pos.x;
			_cursor_position.y += ASSET_FRAME_SIZE.y + 20;
		}
		drawAsset( _cursor_position );
	}
}

void AssetGrid::drawBG( Vector2 _cursor_position )
{
	Rectangle bg_rect;
	bg_rect.x = _cursor_position.x;
	bg_rect.y = _cursor_position.y;
	bg_rect.width = ASSET_GRID_SIZE.x;
	bg_rect.height = ASSET_GRID_SIZE.y;

	DrawRectangleRounded( bg_rect, 0.05f, 7, m_bg_color );
}

void AssetGrid::drawAsset( Vector2& _cursor_position )
{
	auto cursor_position = Vector2( _cursor_position.x += 20, _cursor_position.y + 20 );
	DrawRectangle( cursor_position.x, cursor_position.y, ASSET_FRAME_SIZE.x, ASSET_FRAME_SIZE.y, Color( 217, 217, 217, 255 ) );

	_cursor_position.x += ASSET_FRAME_SIZE.x;
}
