#include "App.h"

#include "UI/Layout.h"
#include "UI/Style.h"

App::App( void )
: m_asset_detail( LAYOUT::ASSETDETAIL::POS, LAYOUT::ASSETDETAIL::SIZE )
, m_asset_grid( LAYOUT::ASSETGRID_POS, LAYOUT::ASSETGRID_SIZE )
{
}

void App::update( const float _tick )
{
	m_notification_manager.update( _tick );
	m_top_bar.update( _tick );
	m_asset_detail.update( _tick );
	m_asset_grid.update( _tick );
}

void App::draw( void )
{
	BeginDrawing();
	ClearBackground( UI::BACKGROUND );
	m_top_bar.draw();
	m_asset_detail.draw();
	m_asset_grid.draw();
	m_notification_manager.draw();
	EndDrawing();
}
