#pragma once

#include <raylib.h>
#include <raymath.h>

namespace UI
{
	// Global Defaults
	constexpr float   MARGIN           = 20.f;
	constexpr float   CORNER_ROUNDNESS = 20.f;

	// Colors
	constexpr Color   PRIMARY             = Color( 182, 25, 91, 255 );
	constexpr Color   BACKGROUND          = Color( 57, 57, 57, 255 );
	constexpr Color   GRADIENT1           = Color( 77, 77, 77, 255 );
	constexpr Color   GRADIENT2           = Color( 97, 97, 97, 255 );
	constexpr Color   GRADIENT3           = Color( 107, 107, 107, 255 );
	constexpr Color   TEXT_COLOR          = Color( 210, 210, 210, 255 );
	constexpr Color   NOTIFICATION        = Color( 87, 87, 87, 255 );
	constexpr Color   NOTIFICATION_ACCENT = Color( 67, 67, 67, 255 );

	// Font sizes
	constexpr int FRAME_FONT_SIZE            = 13;
	constexpr int INPUT_FONT_SIZE            = 16;
	constexpr int DETAIL_TITLE_FONT_SIZE     = 18;
	constexpr int DETAIL_META_DATA_FONT_SIZE = 18;

}
