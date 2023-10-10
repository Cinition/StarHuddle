#include "UIElement.h"

#include "UI/Style.h"

UIElement::UIElement(Vector2& _cursor_position, Vector2 _size)
: m_position( _cursor_position )
, m_size( _size )
{
	_cursor_position.y += _size.y;
}

void UIElement::draw(void)
{
	Vector2 cursor = m_position;

	Rectangle rect;
	rect.x = cursor.x;
	rect.y = cursor.y;
	rect.width = m_size.x;
	rect.height = m_size.y;

	DrawRectangleRounded( rect, m_roundness, 21, UI::ELEMENT_BG_COLOR);

	cursor.x += UI::MARGIN;
	cursor.y += UI::MARGIN;

	if( !getTitle().empty())
	{
		int font_size = 18;
		float text_size = MeasureText( getTitle().c_str(), font_size );
		float title_width = m_size.x - UI::MARGIN * 2;
		auto title_cursor = Vector2( cursor.x + ( title_width / 2 - text_size / 2 ), cursor.y );

		DrawText( getTitle().c_str(), title_cursor.x, title_cursor.y, font_size, UI::TEXT_COLOR);
		cursor.y += font_size + ( UI::MARGIN / 2 ) - 1;

		DrawRectangle( cursor.x, cursor.y, m_size.x - ( UI::MARGIN * 2), 2, UI::ACCENT_COLOR );
		cursor.y += UI::MARGIN / 2 + 1;
	}

	drawChildren();
}
