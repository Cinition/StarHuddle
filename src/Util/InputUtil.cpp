#include "InputUtil.h"

namespace InputUtil
{
	bool isMouseInside( const Vector2& min_position, const Vector2& max_position )
	{
		auto cursor_position    = GetMousePosition();
		auto valid_min_position = ( cursor_position.x > min_position.x && cursor_position.x < max_position.x );
		auto valid_max_position = ( cursor_position.y > min_position.y && cursor_position.y < max_position.y );

		return ( valid_min_position && valid_max_position );
	}
}

