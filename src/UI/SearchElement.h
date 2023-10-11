#pragma once

#include "UI/UIElement.h"

#include "raylib.h"

class SearchElement : public UIElement
{
public:

	SearchElement( void ) = default;
	SearchElement( Vector2& _cursor_position, Vector2 _size );

	void drawInner( Vector2 _cursor_position ) override;
};
