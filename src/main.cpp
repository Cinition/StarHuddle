#include "UI/Style.h"
#include "Utility/FileManager.h"
#include "Layout/FilterBar.h"
#include "Layout/AssetGrid.h"

#include "raylib.h"

int WinMain(void)
{
	Vector2 window_size = Vector2( 1450, 900 );
	InitWindow( window_size.x, window_size.y, "StarHuddle");

	Vector2 filter_bar_size = Vector2( 150.f, window_size.y - ( UI::MARGIN * 2 ) );
	Vector2 asset_grid_size = Vector2( window_size.x - ( filter_bar_size.x + ( UI::MARGIN * 2 ) + UI::MARGIN ), window_size.y - ( UI::MARGIN * 2 ) );

	Vector2 cursor_position = Vector2( UI::MARGIN, UI::MARGIN );
	FilterBar filter_bar = FilterBar( cursor_position, filter_bar_size );
	AssetGrid asset_grid = AssetGrid( cursor_position, asset_grid_size );
	//FileManager file_manager;

	while (!WindowShouldClose())
	{
		// Update pass
		filter_bar.update();
		asset_grid.update();

		// Render pass
		BeginDrawing();
		ClearBackground( Color( 46, 46, 46, 255 ) );

		filter_bar.draw();
		asset_grid.draw();
		//file_manager.draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
