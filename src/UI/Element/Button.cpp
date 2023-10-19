#include "Button.h"

#include "Util/InputUtil.h"
#include "Util/UIUtil.h"
#include "UI/Style.h"

Button::Button( const std::string& _text, const Vector2& _position, const Vector2& _size, callback_function _func )
: UIElement( _position, _size )
, m_callback( _func )
, m_bg_color( UI::PRIMARY )
, m_text( _text )
{
}

Button::Button( Texture2D _icon, const Vector2& _position, const Vector2& _size, callback_function _func )
: UIElement( _position, _size )
, m_callback( _func )
, m_bg_color( UI::PRIMARY )
, m_icon( _icon )
{
}

void Button::update( const float /*_tick*/ )
{
	m_hovered = false;

	if( InputUtil::isMouseInside( m_position, Vector2Add( m_position, m_size ) ) )
	{
		if( IsMouseButtonPressed( MOUSE_BUTTON_LEFT ) )
		{
			m_callback();
			m_pressed = true;
		}
		else
		{
			m_hovered = true;
			m_pressed = false;
		}
	}

	if( m_pressed )
	{
		auto pressed_color = ColorToHSV( UI::PRIMARY );
		pressed_color.z += 0.25f;
		m_bg_color = ColorFromHSV( pressed_color.x, pressed_color.y, pressed_color.z );
	}
	else if( m_hovered )
	{
		auto hovered_color = ColorToHSV( UI::PRIMARY );
		hovered_color.z += 0.15f;
		m_bg_color = ColorFromHSV( hovered_color.x, hovered_color.y, hovered_color.z );
	}
	else
	{
		m_bg_color = UI::PRIMARY;
	}
}

void Button::draw( void )
{
	UIUtil::drawBackground( m_position, m_size, m_bg_color );

	if( !m_text.empty() )
	{
		int     font_size         = 15;
		Vector2 y_center_position = Vector2Add( m_position, Vector2( 0.f, ( m_size.y - font_size ) / 2) );
		UIUtil::drawTextCentered( m_text.c_str(), y_center_position, m_size.x, 15, UI::TEXT_COLOR );
	}
	else
	{
		UIUtil::drawTexture( m_position, m_size, m_icon );
	}

}
