#include "TopBar.h"

#include "Manager/AssetManager.h"
#include "UI/Layout.h"
#include "UI/Style.h"

TopBar::TopBar( void )
: UIElement( Vector2( 0.f, 0.f ), Vector2( 0.f, 0.f ) )
, m_package_button( "Package", LAYOUT::TOPBAR::PACKAGE_POS, LAYOUT::TOPBAR::PACKAGE_SIZE, TopBar::packageAssets )
, m_import_button( LoadTexture( "../data/textures/ImportIcon.png" ), LAYOUT::TOPBAR::IMPORT_POS, LAYOUT::TOPBAR::IMPORT_SIZE, TopBar::importFile )
, m_export_button( LoadTexture( "../data/textures/ExportIcon.png" ), LAYOUT::TOPBAR::EXPORT_POS, LAYOUT::TOPBAR::EXPORT_SIZE, TopBar::exportFile )
, m_search_input( LAYOUT::TOPBAR::SEARCH_POS, LAYOUT::TOPBAR::SEARCH_SIZE )
{
}

void TopBar::update( const float _tick )
{
	m_package_button.update( _tick );
	m_import_button.update( _tick );
	m_export_button.update( _tick );
	m_search_input.update( _tick );
}

void TopBar::draw( void )
{
	m_import_button.draw();
	m_export_button.draw();
	m_search_input.draw();
	m_package_button.draw();
}

void TopBar::packageAssets( void )
{
}

void TopBar::importFile( void )
{
}

void TopBar::exportFile( void )
{
}
