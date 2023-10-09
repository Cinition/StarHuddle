#include "Layout/FilterBar.h"

#include "raylib.h"

int WinMain(void)
{
	InitWindow(800, 450, "StarHuddle");

	Vector2 cursor_pos = Vector2(0.f, 0.f);

	//FileManager file_manager;
	FilterBar filter_bar = { cursor_pos };
	//AssetGrid asset_grid = { cursor_pos };

	while (!WindowShouldClose())
	{
		// Update pass
		filter_bar.update();

		// Render pass
		filter_bar.render();
	}

	CloseWindow();

	return 0;
}
