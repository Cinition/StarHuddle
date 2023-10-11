#pragma once

#include "raylib.h"

#include "UI/Button.h"
#include "UI/UIElement.h"

class DetailBar : public UIElement
{
public:

	DetailBar( void ) = default;
	DetailBar( Vector2& _cursor_position, Vector2 _size );

	void update( void );

private:

	void drawInner( Vector2 _cursor_position ) override;
	static void exportFile( void );

	Button m_export_button;

};
