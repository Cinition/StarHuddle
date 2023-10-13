#include "AssetGrid.h"

#include "UI/Style.h"

#include "raymath.h"

constexpr int   FRAME_ROW_COUNT    = 9;
constexpr float FRAME_ASPECT_RATIO = 1.5f;
constexpr float SCROLL_MULTIPLIER  = 20.f;

AssetGrid::AssetGrid( Vector2& _cursor_position, Vector2 _size )
: UIElement( _cursor_position, _size )
{
	m_asset_grid_size.x  = m_inner_size.x - UI::MARGIN * 2;
	m_grid_render_target = LoadRenderTexture( m_inner_size.x, m_inner_size.y );
	auto frame_width     = ( _size.x - UI::MARGIN ) / FRAME_ROW_COUNT - UI::MARGIN;
	m_frame_size         = Vector2( frame_width, frame_width * FRAME_ASPECT_RATIO );

	m_json_texture       = LoadTexture( "../data/textures/JSON.png" );
	m_tga_texture        = LoadTexture( "../data/textures/TGA.png" );
	m_ogg_texture        = LoadTexture( "../data/textures/OGG.png" );
}

void AssetGrid::update(void)
{
	drawAssetGrid();
	updateScrolling( m_scroll_offset );
}

void AssetGrid::drawAssetGrid( void )
{
	BeginTextureMode( m_grid_render_target );
	ClearBackground( Color( 0.f, 0.f, 0.f, 0.f ) );

	Vector2 cursor_position = Vector2( 0.f, 0.f );
	Vector2 reset_position  = cursor_position;
	cursor_position.y += m_scroll_offset;

	float row_max_height = 0.f;
	m_asset_grid_size.y  = 0.0f;

	for( int i = 0; i < m_temp_asset_count; i++ )
	{
		if( i > 0 && i % FRAME_ROW_COUNT == 0 )
		{
			cursor_position.x = reset_position.x;
			cursor_position.y += row_max_height + UI::MARGIN;
			m_asset_grid_size.y += row_max_height + UI::MARGIN;
			row_max_height = 0.f;
		}

		auto asset_size = drawAsset( cursor_position, "INSERT_BIGGER_NAME", File::Type::TGA );
		row_max_height  = ( asset_size.y > row_max_height ? asset_size.y : row_max_height );

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

Vector2 AssetGrid::drawAsset( Vector2& _cursor_position, const std::string& _name, File::Type _type )
{
	Vector2   asset_size{};
	Texture2D asset_texture;
	switch( _type )
	{
		case File::Type::JSON: asset_texture = m_json_texture; break;
		case File::Type::TGA:  asset_texture = m_tga_texture; break;
		case File::Type::OGG:  asset_texture = m_ogg_texture; break;
		default: _ASSERT( false );
	}

	Rectangle rect{};
	rect.x      = 0.f;
	rect.y      = 0.f;
	rect.height = m_frame_size.y;
	rect.width  = m_frame_size.x;

	DrawTextureRec( asset_texture, rect, _cursor_position, WHITE );
	asset_size = Vector2Add( asset_size, m_frame_size );

	Vector2 text_margin = Vector2( 14, UI::MARGIN / 2  );
	Vector2 text_pos    = Vector2( _cursor_position.x + text_margin.x / 2, _cursor_position.y + m_frame_size.y + text_margin.y );
	Vector2 title_size  = drawTitle( text_pos, m_frame_size.x - text_margin.x, _name );
	asset_size = Vector2Add( asset_size, title_size );

	_cursor_position.x += m_frame_size.x;

	return asset_size;
}

Vector2 AssetGrid::drawTitle( Vector2 _cursor_position, float _available_width, const std::string& _name )
{
	Vector2 title_size{};
	Font    font = GetFontDefault();

	int font_size = 12;
	int column_count = 1;
	title_size    = MeasureTextEx( font, _name.c_str(), font_size, 0.f );

	std::string formatted_text = _name;
	if( title_size.x > _available_width )
	{
		// Rough wrapping calculation
		float average_char_width = title_size.x / static_cast< int >( _name.size() );
		column_count             += static_cast< int >( title_size.x / _available_width );
		title_size.y             = font_size * column_count;
		for (int i = 0; i < column_count; i++)
		{
			auto rough_row_count = _available_width / average_char_width;
			auto row_string      = formatted_text.substr( rough_row_count * i, rough_row_count * ( i + 1 ) );
			auto line_width      = static_cast< int >( row_string.size() ) * average_char_width;

			DrawText( row_string.c_str(), _cursor_position.x + ( ( _available_width - line_width ) / 2 ), _cursor_position.y + ( font_size * i ), font_size, WHITE );
		}
	}
	else
	{
		_cursor_position.x += ( ( _available_width - title_size.x ) / 2 );
		DrawText( formatted_text.c_str(), _cursor_position.x, _cursor_position.y, font_size, WHITE );
	}

	return title_size;
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
