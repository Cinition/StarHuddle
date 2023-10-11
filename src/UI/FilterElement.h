#pragma once

#include "UI/UIElement.h"

#include "raylib.h"

class FilterElement : public UIElement
{
public:

	FilterElement( void ) = default;
	FilterElement( Vector2& _cursor_position, Vector2 _size );

	virtual std::string getTitle( void ) { return "Filters"; }

private:

	virtual void drawChildren( Vector2 _cursor_position ) override;
};
