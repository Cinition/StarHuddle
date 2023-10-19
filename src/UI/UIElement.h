#pragma once

#include "raylib.h"

class UIElement
{
public:

	UIElement( const Vector2& _position, const Vector2& _size )
	: m_position( _position )
	, m_size( _size )
	{}

	virtual void update     ( const float _tick ) = 0;
	virtual void draw       ( void )              = 0;

	auto getPosition( void ) const { return m_position; }
	auto getSize    ( void ) const { return m_size; }

protected:

	Vector2 m_position;
	Vector2 m_size;

};
