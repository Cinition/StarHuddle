#include "AssetGrid.h"

#include "UI/Layout.h"
#include "UI/Style.h"
#include "Util/UIUtil.h"
#include "Manager/AssetManager.h"

constexpr int   FRAME_ROW_COUNT    = 7;
constexpr float FRAME_ASPECT_RATIO = 1.5f;
constexpr float SCROLL_MULTIPLIER  = 20.f;

AssetGrid::AssetGrid( const Vector2& _position, const Vector2& _size )
: UIElement( _position, _size )
{
	Vector2 inner_size   = Vector2Subtract( m_size, Vector2( UI::MARGIN * 2, UI::MARGIN * 2 ) );
	m_grid_render_target = LoadRenderTexture( static_cast< int >( inner_size.x ), static_cast< int >( inner_size.y ) );

	auto frame_width     = ( ( _size.x - ( UI::MARGIN * ( FRAME_ROW_COUNT + 1 ) ) ) / FRAME_ROW_COUNT );
	m_frame_size         = Vector2( frame_width, frame_width * FRAME_ASPECT_RATIO );
}

void AssetGrid::update( const float _tick )
{
	updateAssetGrid( _tick );
	updateScrollOffset();
	drawAssetGrid();
}

void AssetGrid::draw( void )
{
	UIUtil::drawBackground( m_position, m_size, UI::GRADIENT1 );
	UIUtil::drawTexture( Vector2Add( m_position, Vector2( UI::MARGIN, UI::MARGIN ) ), Vector2Subtract( m_size, Vector2( UI::MARGIN, UI::MARGIN ) ), m_grid_render_target.texture, true );
}

void AssetGrid::updateScrollOffset( void )
{
	auto inner_size = Vector2Subtract( m_size, Vector2( UI::MARGIN * 2, UI::MARGIN * 2 ) );
	if( m_asset_grid_size.y <= inner_size.y )
		return; // Don't scroll with no overflow

	auto scroll_delta = GetMouseWheelMove() * 20;
	if( scroll_delta > 0.f && -( m_scroll_offset + scroll_delta ) <= 0.f )
	{
		m_scroll_offset = 0.f; // Push scroll to complete top
		return; // Don't scroll when at top
	}

	auto scroll_distance = m_asset_grid_size.y - inner_size.y;
	if( scroll_delta < 0.f && -( m_scroll_offset + scroll_delta ) >= scroll_distance )
	{
		m_scroll_offset = -scroll_distance; // Push scroll to complete bottom
		return; // Don't scroll when at bottom
	}

	m_scroll_offset += scroll_delta;
}

void AssetGrid::updateAssetGrid( const float _tick )
{
	// Add and/or remove assets to be consistent with AssetManager
	AssetManager asset_manager;
	if( asset_manager.hasAssetsUpdated() )
	{
		m_asset_frames.clear();
		int     asset_index     = 0;
		Vector2 reset_position  = Vector2( 0.f, 0.f );
		Vector2 cursor_position = reset_position;

		for( auto& asset : asset_manager.getAssets() )
		{
			if( asset_index > 0 && asset_index % m_frame_count == 0 )
			{
				cursor_position.x = reset_position.x;
				cursor_position.y += m_frame_size.y + UI::MARGIN;
			}

			m_asset_frames.push_back( { cursor_position, m_frame_size, asset.second } );
			cursor_position.x += m_frame_size.x + UI::MARGIN;
			asset_index += 1;
		}
	}

	// Update frame positions, as text wrapping affects total height of rows and thus next rows position
	int   asset_index         = 0;
	float row_max_height      = 0.f;
	float prev_row_max_height = 0.f;
	m_asset_grid_size.y       = 0.f;

	for( auto& asset : m_asset_frames )
	{
		row_max_height = fmaxf( row_max_height, asset.getSize().y );

		if( asset_index == ( m_asset_frames.size() - 1 ) )
			m_asset_grid_size.y += row_max_height;
		else if( ( asset_index > 0 && asset_index % m_frame_count == 0 ))
			m_asset_grid_size.y += row_max_height + UI::MARGIN;

		if( asset_index > 0 && asset_index % m_frame_count == 0 )
		{
			prev_row_max_height = row_max_height;
			row_max_height      = 0.f;
		}

		asset.updateOffsets( m_scroll_offset, prev_row_max_height );
		asset.update( _tick );
		asset_index += 1;
	}
}

void AssetGrid::drawAssetGrid( void )
{
	BeginTextureMode( m_grid_render_target );
	ClearBackground( Color( 0, 0, 0, 0 ) );

	for( auto& frame : m_asset_frames )
		frame.draw();

	EndTextureMode();
}
