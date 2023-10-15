#pragma once

#include "raylib.h"

#include "Assets/Asset.h"
#include "UI/Button.h"
#include "UI/UIElement.h"

class DetailBar : public UIElement
{
public:

	DetailBar( void ) = default;
	DetailBar( Vector2& _cursor_position, Vector2 _size );

	void update( void );

private:

	void        drawAssetDetail( void );
	void        drawNoSelection( void );
	void        drawAssetIcon( Vector2& _cursor_position, Texture2D _icon );
	void        drawAssetName( Vector2& _cursor_position, const std::string& _text );
	void        drawMetaData( Vector2& _cursor_position, const Asset::MetaData& _meta_data );
	void        drawInner( Vector2 _cursor_position ) override;
	static void exportFile( void );

	Button m_export_button;

};
