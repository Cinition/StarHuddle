#pragma once

#include "UI/UIElement.h"

#include "raylib.h"

class FilterElement : public UIElement
{
public:

	FilterElement( void ) = default;
	FilterElement( Vector2& _cursor_position, Vector2 _size );

	void update( void );
	void drawInner( Vector2 _cursor_position ) override;

private:

	void drawFocused( Vector2 _cursor_position );
	void drawNotFocused( Vector2 _cursor_position );

};
