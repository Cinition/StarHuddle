#pragma once

#include "Asset/Asset.h"
#include "UI/UIElement.h"
#include "UI/Element/Button.h"

#include <raylib.h>

class AssetDetail : UIElement
{
public:

	AssetDetail( const Vector2& _position, const Vector2& _size );

	void update( const float _tick ) override;
	void draw  ( void ) override;

private:

	void drawAssetDetail( void );
	void drawEmptyDetail( void );
	void drawHorizontalLine( Vector2& _cursor_position );
	void drawMetaData( const Asset::MetaData& _meta_data, Vector2& _cursor_position );

};
