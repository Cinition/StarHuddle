#pragma once

#include "UI/UIElement.h"

#include "raylib.h"

class GroupElement : public UIElement
{
public:

	GroupElement( void ) = default;
	GroupElement( Vector2& _cursor_position, Vector2 _size );

	virtual std::string getTitle( void ) { return "Groups"; }

private:

	virtual void drawChildren( void ) override;
};
