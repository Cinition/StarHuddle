#pragma once

#include "UI/SearchElement.h"
#include "UI/FilterElement.h"

class FilterBar
{
public:

	FilterBar( Vector2& _cursor_position, Vector2 _size );

	void update( void );
	void draw( void );

private:

	SearchElement m_search;
	FilterElement m_filter;

};
