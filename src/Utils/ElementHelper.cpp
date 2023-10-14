#include "ElementHelper.h"

bool ElementHelper::mouseInsideUIElement( const UIElement& _element )
{
	auto min_position       = _element.getPosition();
	auto max_position       = Vector2( _element.getPosition().x + _element.getSize().x, _element.getPosition().y + _element.getSize().y );

	return mouseInsideArea( min_position, max_position );
}

bool ElementHelper::mouseInsideArea( const Vector2& _min_position, const Vector2& _max_position )
{
	auto cursor_position    = GetMousePosition();
	auto valid_min_position = ( cursor_position.x > _min_position.x && cursor_position.x < _max_position.x );
	auto valid_max_position = ( cursor_position.y > _min_position.y && cursor_position.y < _max_position.y );

	if( valid_min_position && valid_max_position )
		return true;

	return false;
}
