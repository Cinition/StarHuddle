#pragma once

#include "Asset/Asset.h"
#include "UI/UIElement.h"

#include <raylib.h>

#include <memory>

class AssetFrame : public UIElement
{
public:

	AssetFrame( Vector2& _frame_position, Vector2 _frame_size, std::weak_ptr< Asset > _asset );

	void updateOffsets( const float _scroll_offset, const float _row_offset );
	void update       ( const float _scroll_offset ) override;
	void draw         ( void ) override;

	std::shared_ptr< Asset > getAsset      ( void );

private:

	void drawSelected( Vector2 _position );

	std::weak_ptr< Asset > m_asset;
	Vector2                m_selection_square_size = Vector2( 25.f, 25.f );
	bool                   m_selected              = false;
	float                  m_scroll_offset         = 0.f;
	float                  m_row_offset            = 0.f;

};
