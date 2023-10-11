#include "AssetGrid.h"

#include "UI/Style.h"

constexpr int   FRAME_ROW_COUNT    = 9;
constexpr float FRAME_ASPECT_RATIO = 1.5f;
constexpr float SCROLL_MULTIPLIER  = 20.f;

AssetGrid::AssetGrid( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	m_grid_render_target = LoadRenderTexture( m_inner_size.x, m_inner_size.y );
	auto frame_width     = ( _size.x - UI::MARGIN ) / FRAME_ROW_COUNT - UI::MARGIN;
	m_frame_size         = Vector2( frame_width, frame_width * FRAME_ASPECT_RATIO );
}

void AssetGrid::update(void)
{
	calculateGridSize( m_temp_asset_count, m_frame_size );
	updateScrolling( m_scroll_offset );
}

void AssetGrid::drawAssetGrid( void )
{
	BeginTextureMode( m_grid_render_target );
	ClearBackground( Color( 0.f, 0.f, 0.f, 0.f ) );

	Vector2 cursor_position = Vector2( 0.f, 0.f );
	Vector2 reset_position  = cursor_position;
	cursor_position.y += m_scroll_offset;

	for( int i = 0; i < m_temp_asset_count; i++ )
	{
		if( i > 0 && i % FRAME_ROW_COUNT == 0 )
		{
			cursor_position.x = reset_position.x;
			cursor_position.y += m_frame_size.y + UI::MARGIN;
		}

		if( ( cursor_position.y + m_frame_size.y ) < reset_position.y )
			continue; // Don't render asset if its too high

		if( cursor_position.y > ( m_position.y + UI::MARGIN + m_inner_size.y ) )
			continue; // Don't render asset if its too low

		drawAsset( cursor_position, Vector2( 0.f, 0.f ) );
		cursor_position.x += UI::MARGIN;
	}

	EndTextureMode();
}

void AssetGrid::drawInner( Vector2 _cursor_position )
{
	Rectangle rect;
	rect.x      = 0.f;
	rect.y      = 0.f;
	rect.height = -m_grid_render_target.texture.height;
	rect.width  = m_grid_render_target.texture.width;
	DrawTextureRec( m_grid_render_target.texture, rect, _cursor_position, Color( 255, 255, 255, 255 ) );
}

void AssetGrid::drawAsset( Vector2& _cursor_position, Vector2 _cutoff )
{
	DrawRectangle( _cursor_position.x, _cursor_position.y, m_frame_size.x, m_frame_size.y, Color( 217, 217, 217, 255 ) );
	_cursor_position.x += m_frame_size.x;
}

void AssetGrid::updateScrolling( float& _scroll_offset )
{
	if( m_asset_grid_size.y <= m_inner_size.y )
		return; // Don't scroll with no overflow

	auto scroll_delta = GetMouseWheelMove() * SCROLL_MULTIPLIER;
	if( scroll_delta > 0.f && -( _scroll_offset + scroll_delta ) <= 0.f )
	{
		_scroll_offset = 0.f; // Push scroll to complete top
		return; // Don't scroll when at top
	}

	auto inner_height    = m_size.y - ( UI::MARGIN * 2 );
	auto scroll_distance = m_asset_grid_size.y - inner_height;
	if( scroll_delta < 0.f && -( _scroll_offset + scroll_delta ) >= scroll_distance )
	{
		_scroll_offset = -scroll_distance; // Push scroll to complete bottom
		return; // Don't scroll when at bottom
	}

	_scroll_offset += scroll_delta;
}

void AssetGrid::calculateGridSize( int _asset_count, Vector2 _frame_size )
{
	float row_size     = ( _frame_size.x * FRAME_ROW_COUNT ) + ( UI::MARGIN * ( FRAME_ROW_COUNT - 1 ) );
	float column_count = floor( _asset_count / FRAME_ROW_COUNT );
	float column_size  = ( _frame_size.y * column_count ) + ( UI::MARGIN * ( column_count - 1 ) );

	m_asset_grid_size = Vector2( row_size, column_size );
}
