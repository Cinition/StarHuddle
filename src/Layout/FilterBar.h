#pragma once

#include "UI/Button.h"
#include "UI/UIElement.h"
#include "UI/FilterElement.h"
#include "UI/GroupElement.h"

class FilterBar
{
public:

	FilterBar( Vector2& _cursor_position, Vector2 _size );

	void update();
	void draw( void );

private:

	static void addFile( void );

	Button m_add_file_button;
	FilterElement m_filters;
	GroupElement m_groups;

};
