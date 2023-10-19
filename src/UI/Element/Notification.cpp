#include "Notification.h"

#include "UI/Style.h"

constexpr float TIMOUT_TIME = 5.f;

Notification::Notification( const std::string& _text )
: m_text( _text )
{
	float inner_width        = m_popup_size.x - ( UI::MARGIN * 2 );
	int   text_width         = MeasureText( m_text.c_str(), m_font_size );
	float average_char_width = static_cast< float >( text_width ) / static_cast< int >( m_text.size() );

	for( int i = 1; i < text_width / inner_width ; i++ )
	{
		m_columns += 1;
		m_text.insert( static_cast< size_t >( inner_width / average_char_width * i ), "\n" );
	}

	m_popup_size.y = static_cast< float >( m_font_size * m_columns + ( UI::MARGIN * 2 ) );
}

void Notification::update( void )
{
	m_notification_timer += GetFrameTime();

	if( m_notification_timer < TIMOUT_TIME )
		return;

	alive = false;
}

void Notification::draw( Vector2& _cursor_position )
{
	_cursor_position.y -= m_popup_size.y + UI::MARGIN;

	RaylibRectangle rect;
	rect.x      = _cursor_position.x;
	rect.y      = _cursor_position.y;
	rect.height = m_popup_size.y;
	rect.width  = m_popup_size.x;

	RaylibRectangle shadow_rect = rect;
	shadow_rect.x += 5.f;
	shadow_rect.y += 5.f;

	DrawRectangleRounded( shadow_rect, 0.25f, 11, UI::NOTIFICATION_ACCENT );
	DrawRectangleRounded( rect, 0.25f, 11, UI::NOTIFICATION );

	Vector2 text_pos = Vector2( _cursor_position.x + UI::MARGIN, _cursor_position.y + UI::MARGIN );
	RaylibDrawText( m_text.c_str(), static_cast< int >( text_pos.x ), static_cast< int >( text_pos.y ), m_font_size, UI::TEXT_COLOR );
}
