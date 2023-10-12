#pragma once

#include "UI/UIElement.h"
#include "Files/File.h"

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
	void drawAsset( Vector2& _cursor_position, const std::string& _name, File::Type _type );
	void updateScrolling( float& _scroll_offset );
	void calculateGridSize( int _asset_count, Vector2 _asset_size );

	RenderTexture2D m_grid_render_target;
	Texture2D       m_json_texture;
	Texture2D       m_tga_texture;
	Texture2D       m_ogg_texture;
	Vector2         m_frame_size       = Vector2( 0.f, 0.f );
	Vector2         m_asset_grid_size  = Vector2( 0.f, 0.f );
	int             m_temp_asset_count = 80;
	float           m_scroll_offset    = 0.0f;
};
