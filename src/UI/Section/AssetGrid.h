#pragma once

#include "Asset/Asset.h"
#include "UI/UIElement.h"
#include "UI/Element/AssetFrame.h"

#include <raylib.h>

class AssetGrid : public UIElement
{
public:

	AssetGrid( const Vector2& _cursor_position, const Vector2& _size );

	void update( const float _tick ) override;
	void draw  ( void ) override;

private:

	void updateScrollOffset( void );
	void updateAssetGrid   ( const float _tick );
	void drawAssetGrid     ( void );

	std::vector< AssetFrame > m_asset_frames;
	RenderTexture2D           m_grid_render_target;
	Vector2                   m_frame_size      = Vector2( 0.f, 0.f );
	Vector2                   m_asset_grid_size = Vector2( 0.f, 0.f );
	float                     m_scroll_offset   = 0.0f;
	const int                 m_frame_count     = 7;
};
