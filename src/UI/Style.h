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
	constexpr Color   PRIMARY          = Color( 182.f, 25.f, 91.f, 255.f );
	constexpr Color   ACCENT1          = Color( 57.f, 57.f, 57.f, 255.f );
	constexpr Color   ACCENT2          = Color( 77.f, 77.f, 77.f, 255.f );
	constexpr Color   ACCENT3          = Color( 97.f, 97.f, 97.f, 255.f );
	constexpr Color   ACCENT4          = Color( 107.f, 107.f, 107.f, 255.f );
	constexpr Color   TEXT_COLOR       = Color( 210.f, 210.f, 210.f, 255.f );

	inline float getCornerRoundness( Vector2 _element_size ) { return ( UI::CORNER_ROUNDNESS / fmin( _element_size.x, _element_size.y ) ); }

}
