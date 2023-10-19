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

	void update( const float _tick );
	void draw  ( void );

private:

	Vector2 m_screen_size = { 1470.f, 870.f };

	AssetDetail         m_asset_detail;
	AssetGrid           m_asset_grid;
	TopBar              m_top_bar;
	NotificationManager m_notification_manager;

};
