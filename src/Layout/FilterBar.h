#pragma once

#include "UI/Button.h"

class FilterBar
{

public:

	FilterBar( Vector2& _cursor_pos );

	void update();
	void render();

private:

	static void addFile( void );

	Button m_add_file_button;

};
