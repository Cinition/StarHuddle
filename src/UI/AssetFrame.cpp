#include "AssetFrame.h"

#include "Assets/AssetManager.h"
#include "UI/Style.h"
#include "Utils/ElementHelper.h"

#include "raymath.h"

AssetFrame::AssetFrame( Vector2& _frame_position, Vector2 _frame_size, std::weak_ptr< Asset > _asset )
: m_position( _frame_position )
, m_size( _frame_size )
, m_asset( std::move( _asset ) )
{
}

void AssetFrame::update( Vector2 _input_min, Vector2 _input_max )
{
	if( !ElementHelper::mouseInsideArea( _input_min, Vector2Add( _input_max, Vector2Negate( _input_min ) ) ) )
		return;

	detectSelection( Vector2Add( m_position, Vector2Add( _input_min, Vector2( UI::MARGIN, UI::MARGIN ) ) ) );
	checkIfSelected();
}

Vector2 AssetFrame::draw( float _scroll_offset )
{
	auto origin_position = Vector2( m_position.x, m_position.y + _scroll_offset );
	auto cursor_position = origin_position;
	drawBackground( cursor_position );

	cursor_position = Vector2Add( cursor_position, Vector2( UI::MARGIN, UI::MARGIN ) );
	drawIcon( cursor_position );

	cursor_position = Vector2Add( cursor_position, Vector2( 0.f, UI::MARGIN / 2 ) );
	drawTitle( cursor_position );

	// Only calculate asset frame height, as that's dynamic
	m_size.y = cursor_position.y - origin_position.y;

	cursor_position = Vector2Add( m_position, Vector2( m_size.x - UI::MARGIN / 2 - m_selection_square_size.x, _scroll_offset + UI::MARGIN / 2 ) );
	drawSelected( cursor_position );

	return m_size;
}

std::shared_ptr< Asset > AssetFrame::getAsset( void )
{
	auto locked_asset = m_asset.lock();
	if( locked_asset )
		return locked_asset;

	return nullptr;
}

void AssetFrame::detectSelection( Vector2 _absolute_position )
{
	if( ElementHelper::mouseInsideArea( _absolute_position, Vector2Add( _absolute_position, m_size ) ) )
	{
		if( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) )
		{
			auto locked_asset = getAsset();
			if( !locked_asset )
				return;

			AssetManager::addSelection( locked_asset->getHash() );
		}
	}
}

void AssetFrame::checkIfSelected( void )
{
	auto locked_asset = getAsset();
	if( !locked_asset )
		return;

	auto selection_vector = AssetManager::getAssetSelection();
	auto selection_it     = std::find_if(
        selection_vector.begin(), selection_vector.end(),
        [ locked_asset ]( size_t _selection_hash )
        {
            return ( _selection_hash == locked_asset->getHash() );
        } );

	m_selected = ( selection_it != selection_vector.end() );

}


void AssetFrame::drawBackground( Vector2& _cursor_position )
{
	Rectangle rect;
	rect.x = _cursor_position.x;
	rect.y = _cursor_position.y;
	rect.width = m_size.x;
	rect.height = m_size.y;

	DrawRectangleRounded( rect, UI::getCornerRoundness( m_size ), 11, UI::ACCENT3 );
}

void AssetFrame::drawIcon( Vector2& _cursor_position )
{
	Texture2D asset_texture{};
	auto      asset = getAsset();
	if( !asset )
		asset_texture = LoadTexture( "data/texture/Undefined.png" );
	else
	{
		switch( asset->getType() )
		{
			case Asset::Type::JSON: asset_texture = LoadTexture( "../data/textures/JSON.png" ); break;
			case Asset::Type::TGA: asset_texture = LoadTexture( "../data/textures/TGA.png" ); break;
			case Asset::Type::OGG: asset_texture = LoadTexture( "../data/textures/OGG.png" ); break;
		}
	}

	Rectangle texture_rect;
	texture_rect.x = 0.f;
	texture_rect.y = 0.f;
	texture_rect.width = asset_texture.width;
	texture_rect.height = asset_texture.height;

	Rectangle rect;
	rect.x = _cursor_position.x;
	rect.y = _cursor_position.y;
	rect.width = m_size.x - ( UI::MARGIN * 2 );
	rect.height = texture_rect.height * ( rect.width / texture_rect.width);

	DrawTexturePro( asset_texture, texture_rect, rect, { 0.f, 0.f }, 0.f, WHITE );
	//DrawTextureRec( asset_texture, rect, _cursor_position, WHITE );
	_cursor_position.y += rect.height;
}

void AssetFrame::drawTitle( Vector2& _cursor_position )
{
	std::string title;
	auto asset = getAsset();
	if( !asset )
		title = "";
	else
		title = asset->getName();

	int         column_count    = 1;
	int         font_size       = 12;
	Font        font            = GetFontDefault();
	Vector2     title_size      = MeasureTextEx( font, title.c_str(), font_size, 0.f );
	float       available_width = m_size.x - ( UI::MARGIN );

	std::string formatted_text = title;
	if( title_size.x > available_width )
	{
		// Rough wrapping calculation
		float average_char_width = title_size.x / static_cast< int >( formatted_text.size() );
		column_count             += static_cast< int >( title_size.x / available_width );
		title_size.y             = font_size * column_count;
		for (int i = 0; i < column_count; i++)
		{
			auto rough_row_count = available_width / average_char_width;
			auto row_string      = formatted_text.substr( rough_row_count * i, rough_row_count * ( i + 1 ) );
			auto line_width      = static_cast< int >( row_string.size() ) * average_char_width;

			DrawText( row_string.c_str(), _cursor_position.x + ( ( available_width - line_width ) / 2 ), _cursor_position.y + ( font_size * i ), font_size, WHITE );
			_cursor_position.y += font_size;
		}
		_cursor_position.y += UI::MARGIN / 2;
	}
	else
	{
		_cursor_position.x += ( ( available_width - title_size.x ) / 2 );
		DrawText( formatted_text.c_str(), _cursor_position.x, _cursor_position.y, font_size, WHITE );
		_cursor_position.y += font_size;
		_cursor_position.y += UI::MARGIN / 2;
	}
}

void AssetFrame::drawSelected( Vector2& _cursor_position )
{
	Rectangle rect;
	rect.x      = _cursor_position.x;
	rect.y      = _cursor_position.y;
	rect.width  = m_selection_square_size.x;
	rect.height = m_selection_square_size.y;

	if( m_selected )
		DrawRectangle( rect.x, rect.y, rect.width, rect.height, UI::PRIMARY );
	else
		DrawRectangleLinesEx( rect, 5, UI::PRIMARY );
}
