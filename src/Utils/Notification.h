#pragma once

#include "raylib.h"

#include <string>

class Notification
{

public:

	Notification( const std::string& _text );

	void update( void );
	void draw( Vector2& _cursor_position );

	bool alive = true;

private:

	std::string m_text;
	Vector2     m_popup_size         = Vector2( 250, 80 );
	int         m_font_size          = 10;
	int         m_columns            = 1;
	float       m_notification_timer = 0.f;
	bool        m_fade               = false;

};
