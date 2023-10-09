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

	Button m_add_file_button;
};
