#pragma once

#include "raylib.h"

#include "UI/UIElement.h"

namespace ElementHelper
{
	extern bool mouseInsideUIElement( const UIElement& _element );
	extern bool mouseInsideArea( const Vector2& _position, const Vector2& _size );
}
