#include "AssetFrame.h"

#include "Manager/AssetManager.h"
#include "UI/Style.h"
#include "Util/UIUtil.h"
#include "Util/InputUtil.h"

#include "raymath.h"

AssetFrame::AssetFrame( Vector2& _frame_position, Vector2 _frame_size, std::weak_ptr< Asset > _asset )
: UIElement( _frame_position, _frame_size )
, m_asset( std::move( _asset ) )
{
	int total_text_width = MeasureText( m_asset.lock()->getName().c_str(), UI::FRAME_FONT_SIZE );
	m_size.y += static_cast< float >( total_text_width * UI::FRAME_FONT_SIZE );
}

void AssetFrame::updateOffsets( const float _scroll_offset, const float _row_offset )
{
	m_scroll_offset   = _scroll_offset;
	m_row_offset      = _row_offset;
}

void AssetFrame::update( const float /*_tick*/ )
{
	auto locked_asset = getAsset();
	if( !locked_asset )
		return;

	if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
		AssetManager::addSelection( locked_asset->getHash() );

	auto selection_vector = AssetManager::getAssetSelection();
	auto selection_it     = std::find_if(
        selection_vector.begin(), selection_vector.end(),
        [ locked_asset ]( size_t _selection_hash )
        {
            return ( _selection_hash == locked_asset->getHash() );
        } );

	m_selected = ( selection_it != selection_vector.end() );
}

void AssetFrame::draw( void )
{
	auto locked_asset = getAsset();
	if( !locked_asset )
		return;

	auto origin_position = Vector2( m_position.x, m_position.y + m_scroll_offset + m_row_offset );
	auto cursor_position = origin_position;

	UIUtil::drawBackground( cursor_position, m_size, UI::GRADIENT2 );

	cursor_position = Vector2Add( cursor_position, Vector2( UI::MARGIN, UI::MARGIN ) );
	Texture2D icon  = locked_asset->getIcon();
	UIUtil::drawTexture( cursor_position, Vector2( static_cast< float >( icon.width ), static_cast< float >( icon.height ) ), icon );

	cursor_position = Vector2Add( cursor_position, Vector2( -UI::MARGIN / 2, UI::MARGIN / 2 ) );
	UIUtil::drawTextCentered( locked_asset->getName().c_str(), cursor_position, Vector2Subtract( m_size, Vector2( UI::MARGIN, UI::MARGIN ) ).x, 16, UI::TEXT_COLOR );

	cursor_position = Vector2Add( m_position, Vector2( m_size.x - UI::MARGIN / 2 - m_selection_square_size.x, m_scroll_offset + UI::MARGIN / 2 ) );
	drawSelected( cursor_position );
}

std::shared_ptr< Asset > AssetFrame::getAsset( void )
{
	auto locked_asset = m_asset.lock();
	if( locked_asset )
		return locked_asset;

	return nullptr;
}

void AssetFrame::drawSelected( Vector2 _position )
{
	RaylibRectangle rect;
	rect.x      = _position.x;
	rect.y      = _position.y;
	rect.width  = m_selection_square_size.x;
	rect.height = m_selection_square_size.y;

	if( m_selected )
		DrawRectangle( static_cast< int >( rect.x ), static_cast< int >( rect.y ), static_cast< int >( rect.width ), static_cast< int >( rect.height ), UI::PRIMARY );
	else
		DrawRectangleLinesEx( rect, 5, UI::PRIMARY );
}