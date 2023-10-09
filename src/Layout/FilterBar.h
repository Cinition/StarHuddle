#pragma once

#include "UI/Button.h"

class FilterBar
{

public:

	FilterBar( void );

	void update();
	void render( Vector2& _cursor_position );

private:

	static void addFile( void );

	void drawFilters( Vector2& _cursor_position );
	void drawGroups( Vector2& _cursor_position );

	Button m_add_file_button;
	Color m_bg_color;
};
