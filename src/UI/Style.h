#pragma once

#include "raylib.h"
#include "raymath.h"

namespace UI
{
	// Global Defaults
	constexpr int     MARGIN           = 20;
	constexpr float   CORNER_ROUNDNESS = 20.f;
	constexpr Vector2 SCREEN_SIZE      = Vector2( 1470.f, 870.f );

	// Colors
	constexpr Color   PRIMARY          = Color( 182, 25, 91, 255 );
	constexpr Color   ACCENT1          = Color( 57, 57, 57, 255 );
	constexpr Color   ACCENT2          = Color( 77, 77, 77, 255 );
	constexpr Color   ACCENT3          = Color( 97, 97, 97, 255 );
	constexpr Color   ACCENT4          = Color( 107, 107, 107, 255 );
	constexpr Color   TEXT_COLOR       = Color( 210, 210, 210, 255 );

	inline float getCornerRoundness( Vector2 _element_size ) { return UI::CORNER_ROUNDNESS / fminf( _element_size.x, _element_size.y ); }

}
