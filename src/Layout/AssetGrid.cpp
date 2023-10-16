#include "AssetGrid.h"

#include "UI/Style.h"
#include "Assets/AssetManager.h"
#include "Utils/ElementHelper.h"

#include "raymath.h"

constexpr int   FRAME_ROW_COUNT    = 7;
constexpr float FRAME_ASPECT_RATIO = 1.5f;
constexpr float SCROLL_MULTIPLIER  = 20.f;

AssetGrid::AssetGrid( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	m_asset_grid_size.x  = m_inner_size.x - UI::MARGIN * 2;
	m_grid_render_target = LoadRenderTexture( static_cast< int >( m_inner_size.x ), static_cast< int >( m_inner_size.y ) );
	auto frame_width     = ( ( _size.x - ( UI::MARGIN * ( FRAME_ROW_COUNT + 1 ) ) ) / FRAME_ROW_COUNT );
	m_frame_size         = Vector2( frame_width, frame_width * FRAME_ASPECT_RATIO );
}

void AssetGrid::update(void)
{
	// Don't like this solution, but
	// it's the only way without making this an immidiate mode interface
	AssetManager asset_manager;
	if( asset_manager.hasAssetsUpdated() )
	{
		m_asset_frames.clear();
		int     asset_index     = 0;
		Vector2 reset_position  = Vector2( 0.f, 0.f );
		Vector2 cursor_position = reset_position;

		for( auto& asset : asset_manager.getAssets() )
		{
			if( asset_index > 0 && asset_index % FRAME_ROW_COUNT == 0 )
			{
				cursor_position.x = reset_position.x;
				cursor_position.y += m_frame_size.y + UI::MARGIN;
			}

			m_asset_frames.push_back( { cursor_position, m_frame_size, asset } );
			cursor_position.x += m_frame_size.x + UI::MARGIN;
			asset_index += 1;
		}
	}

	for( auto& frame : m_asset_frames )
		frame.update( m_position, Vector2Add( m_position, m_size ) );

	drawAssetGrid();
	updateScrolling( m_scroll_offset );
}

void AssetGrid::drawAssetGrid( void )
{
	BeginTextureMode( m_grid_render_target );
	ClearBackground( Color( 0, 0, 0, 0 ) );

	Vector2 reset_position  = Vector2( 0.f, 0.f );
	Vector2 cursor_position = reset_position;
	cursor_position.y += m_scroll_offset;

	int asset_index      = 0;
	float row_max_height = 0.f;
	m_asset_grid_size.y  = 0.f;

	for( auto& asset : m_asset_frames )
	{
		if( asset_index == ( m_asset_frames.size() - 1 ) )
			m_asset_grid_size.y += row_max_height;
		else if( ( asset_index > 0 && asset_index % FRAME_ROW_COUNT == 0 ))
			m_asset_grid_size.y += row_max_height + UI::MARGIN;

		if( asset_index > 0 && asset_index % FRAME_ROW_COUNT == 0 )
		{
			cursor_position.x = reset_position.x;
			cursor_position.y += row_max_height + UI::MARGIN;
			row_max_height = 0.f;
		}


		auto asset_size = asset.draw( m_scroll_offset );
		row_max_height  = ( asset_size.y > row_max_height ? asset_size.y : row_max_height );

		cursor_position.x += UI::MARGIN;
		asset_index       += 1;
	}

	EndTextureMode();
}

void AssetGrid::drawInner( Vector2 _cursor_position )
{
	RaylibRectangle rect;
	rect.x      = 0.f;
	rect.y      = 0.f;
	rect.height = static_cast< float >( -m_grid_render_target.texture.height );
	rect.width  = static_cast< float >( m_grid_render_target.texture.width );
	DrawTextureRec( m_grid_render_target.texture, rect, _cursor_position, Color( 255, 255, 255, 255 ) );
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
