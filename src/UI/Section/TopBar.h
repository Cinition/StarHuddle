#pragma once

#include "UI/UIElement.h"
#include "UI/Element/Input.h"
#include "UI/Element/Button.h"

class TopBar : public UIElement
{
public:

	TopBar( void );

	void update( const float _tick ) override;
	void draw  ( void ) override;

private:

	static void packageAssets( void );
	static void importFile   ( void );
	static void exportFile   ( void );

	Button m_package_button;
	Button m_import_button;
	Button m_export_button;
	Input  m_search_input;

};
