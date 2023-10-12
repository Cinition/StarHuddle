#include "UIElement.h"

#include "UI/Style.h"

#include "raymath.h"

UIElement::UIElement( Vector2& _cursor_position, Vector2 _size )
: m_position( _cursor_position )
, m_size( _size )
, m_inner_size( Vector2( m_size.x - UI::MARGIN * 2, m_size.y - UI::MARGIN * 2 ) )
{
}

void UIElement::draw( void )
{
	Vector2 cursor = m_position;

	Rectangle rect;
	rect.x = cursor.x;
	rect.y = cursor.y;
	rect.width = m_size.x;
	rect.height = m_size.y;

	float pixel_percentage = m_roundness / fmin( m_size.x, m_size.y );

	DrawRectangleRounded( rect, pixel_percentage, 11, UI::ELEMENT_BG_COLOR);

	if( m_use_inner_margin )
	{
		cursor.x += UI::MARGIN;
		cursor.y += UI::MARGIN;
	}

	drawInner( cursor );
}
