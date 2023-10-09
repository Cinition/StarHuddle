#include "Utility/FileManager.h"
#include "Layout/FilterBar.h"
#include "Layout/AssetGrid.h"

#include "raylib.h"

int WinMain(void)
{
	InitWindow(1500, 940, "StarHuddle");

	//FileManager file_manager;
	FilterBar filter_bar;
	AssetGrid asset_grid;

	while (!WindowShouldClose())
	{
		// Update pass
		filter_bar.update();

		// Render pass
		BeginDrawing();
		ClearBackground( Color( 46, 46, 46, 255 ) );

		Vector2 cursor_pos = Vector2( 15.f, 15.f );

		filter_bar.render( cursor_pos );

		// Reset cursor
		cursor_pos = Vector2( 180.f, 15.f );

		asset_grid.render( cursor_pos );

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
