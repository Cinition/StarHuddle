#pragma once

#include "raylib.h"

class AssetGrid
{

public:

	AssetGrid( void );

	void update();
	void render( Vector2& _cursor_position );

private:

	void drawBG( Vector2 _cursor_position );
	void drawAsset( Vector2& _cursor_position );

	Color m_bg_color;
};
