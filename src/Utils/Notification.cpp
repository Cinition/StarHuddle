#include "Notification.h"

#include "UI/Style.h"

constexpr float   TIMOUT_TIME = 5.f;
constexpr float   FADE_TIME   = 1.f;

Notification::Notification( const std::string& _text )
: m_text( _text )
{
	float inner_width = m_popup_size.x - ( UI::MARGIN * 2 );
	auto  text_size   = MeasureTextEx( GetFontDefault(), m_text.c_str(), m_font_size, 0.f );
	float average_char_width = text_size.x / static_cast< int >( m_text.size() );

	for( int i = 1; i < text_size.x / inner_width ; i++ )
	{
		m_columns += 1;
		m_text.insert( static_cast< size_t >( average_char_width * inner_width) , "\n" );
	}
}

void Notification::update( void )
{
	m_notification_timer += GetFrameTime();

	if( m_notification_timer < TIMOUT_TIME )
		return;

	m_fade = true;
	if( m_notification_timer < ( TIMOUT_TIME + FADE_TIME ) )
		return;

	alive = false;
}

void Notification::draw( Vector2& _cursor_position )
{
	Rectangle rect;
	rect.x      = _cursor_position.x;
	rect.y      = _cursor_position.y;
	rect.height = m_popup_size.y + ( 12 * ( m_columns - 1 ) );
	rect.width  = m_popup_size.x;

	Rectangle shadow_rect = rect;
	shadow_rect.x += 5.f;
	shadow_rect.y += 5.f;

	_cursor_position.y += rect.height + UI::MARGIN;

	DrawRectangleRounded( shadow_rect, 0.25f, 11, UI::BACKGROUND_COLOR );
	DrawRectangleRounded( rect, 0.25f, 11, UI::ELEMENT_BG_COLOR );

	Vector2 text_pos = Vector2( _cursor_position.x + UI::MARGIN, _cursor_position.y + UI::MARGIN );
	DrawText( m_text.c_str(), text_pos.x, text_pos.y, 10, UI::TEXT_COLOR );
}