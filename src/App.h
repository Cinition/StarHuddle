#pragma once

#include "UI/Section/AssetDetail.h"
#include "UI/Section/AssetGrid.h"
#include "UI/Section/TopBar.h"
#include "Manager/NotificationManager.h"

#include <raylib.h>

class App
{
public:

	App( void );

	void handleDragIn( void );
	void update      ( const float _tick );
	void draw        ( void );

private:

	AssetDetail         m_asset_detail;
	AssetGrid           m_asset_grid;
	TopBar              m_top_bar;
	NotificationManager m_notification_manager;

};
