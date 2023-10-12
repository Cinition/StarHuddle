#include "UI/Style.h"
#include "Files/FileManager.h"
#include "Layout/FilterBar.h"
#include "Layout/DetailBar.h"
#include "Layout/AssetGrid.h"

#include "raylib.h"

int WinMain(void)
{
	FileManager file_manager;

	Vector2 window_size = Vector2( 1450, 870 );
	InitWindow( window_size.x, window_size.y, "StarHuddle");

	auto      full_inner_size = Vector2( window_size.x - ( UI::MARGIN * 2 ), window_size.y - ( UI::MARGIN * 2 ) );

	Vector2   detail_bar_size = Vector2( 200.f, full_inner_size.y );
	Vector2   filter_bar_size = Vector2( full_inner_size.x - detail_bar_size.x - UI::MARGIN, 50 );
	Vector2   asset_grid_size = Vector2( full_inner_size.x - detail_bar_size.x - UI::MARGIN, full_inner_size.y - filter_bar_size.y - UI::MARGIN );

	Vector2   cursor_position = Vector2( UI::MARGIN, UI::MARGIN );
	FilterBar filter_bar      = FilterBar( cursor_position, filter_bar_size );

	cursor_position           = Vector2( UI::MARGIN, UI::MARGIN + filter_bar_size.y + UI::MARGIN ); // Cursor Repositions
	AssetGrid asset_grid      = AssetGrid( cursor_position, asset_grid_size );

	cursor_position           = Vector2( UI::MARGIN + filter_bar_size.x + UI::MARGIN, UI::MARGIN ); // Cursor Repositions
	DetailBar detail_bar      = DetailBar( cursor_position, detail_bar_size );

	while (!WindowShouldClose())
	{
		// Update pass

		if( IsFileDropped() )
		{
			auto dropped_files = LoadDroppedFiles();

			for( int i = 0; i < dropped_files.count; i++ )
			{
				auto file_path = std::string( dropped_files.paths[ i ] );
				file_manager.importFiles( file_path );
			}

			UnloadDroppedFiles( dropped_files );
		}

		filter_bar.update();
		asset_grid.update();
		detail_bar.update();

		// Specific render for overflow issue
		asset_grid.drawAssetGrid();

		// Render pass
		BeginDrawing();
		ClearBackground( UI::BACKGROUND_COLOR );

		asset_grid.draw();
		filter_bar.draw();
		detail_bar.draw();

		EndDrawing();
	}

	RaylibCloseWindow();

	return 0;
}
