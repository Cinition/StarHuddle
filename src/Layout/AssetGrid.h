#pragma once

#include "UI/UIElement.h"

#include "raylib.h"

class AssetGrid : public UIElement
{

public:

	AssetGrid( void ) = default;
	AssetGrid( Vector2& _cursor_position, Vector2 _size );

private:

	virtual void drawChildren( void ) override;
	void drawAsset( Vector2& _cursor_position, Vector2 _cutoff );

	float m_scroll_offset = 0.0f;
};
