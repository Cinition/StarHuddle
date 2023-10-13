#pragma once

#include "UI/UIElement.h"

#include "raylib.h"

#include <string>

class SearchElement : public UIElement
{
public:

	SearchElement( void ) = default;
	SearchElement( Vector2& _cursor_position, Vector2 _size );

	void update( void );
	void drawInner( Vector2 _cursor_position ) override;

private:

	void drawFocused( Vector2 _cursor_position );
	void drawNotFocused( Vector2 _cursor_position );

	std::string m_input;

};
