#pragma once

#include "UI/UIElement.h"
#include "Assets/Asset.h"

#include "raylib.h"

class AssetGrid : public UIElement
{

public:

	AssetGrid( void ) = default;
	AssetGrid( Vector2& _cursor_position, Vector2 _size );

	void update( void );
	void drawAssetGrid( void );

private:

	void drawInner( Vector2 _cursor_position ) override;
	void updateScrolling( float& _scroll_offset );
	Vector2 drawAsset( Vector2& _cursor_position, const std::string& _name, Asset::Type _type );
	Vector2 drawTitle( Vector2 _cursor_position, float _available_width, const std::string& _name );

	RenderTexture2D m_grid_render_target;
	Texture2D       m_json_texture;
	Texture2D       m_tga_texture;
	Texture2D       m_ogg_texture;
	Vector2         m_frame_size       = Vector2( 0.f, 0.f );
	Vector2         m_asset_grid_size  = Vector2( 0.f, 0.f );
	float           m_scroll_offset    = 0.0f;
};
