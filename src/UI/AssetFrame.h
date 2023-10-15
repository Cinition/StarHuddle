#pragma once

#include "Assets/Asset.h"

#include "raylib.h"

#include <memory>

class AssetFrame
{
public:

	AssetFrame( void ) = default;
	AssetFrame( Vector2& _frame_position, Vector2 _frame_size, std::weak_ptr< Asset > _asset );

	void    update( Vector2 _input_min, Vector2 _input_max );
	Vector2 draw( float _scroll_offset );

	std::shared_ptr< Asset > getAsset( void );

private:

	void detectSelection( Vector2 _absolute_position );
	void checkIfSelected( void );
	void drawBackground( Vector2& _cursor_position );
	void drawIcon( Vector2& _cursor_position );
	void drawTitle( Vector2& _cursor_position );
	void drawSelected( Vector2& _cursor_position );

	std::weak_ptr< Asset > m_asset;
	Vector2                m_position;
	Vector2                m_size;
	Vector2                m_selection_square_size = Vector2( 25.f, 25.f );
	bool                   m_selected              = false;
	float                  m_last_scroll_offset    = 0.f;

};
