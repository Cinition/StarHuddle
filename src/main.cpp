#include "UI/Style.h"
#include "Assets/AssetManager.h"
#include "Layout/FilterBar.h"
#include "Layout/DetailBar.h"
#include "Layout/AssetGrid.h"

#include "raylib.h"

int WinMain(void)
{
	AssetManager asset_manager;

	InitWindow( static_cast< int >( UI::SCREEN_SIZE.x ), static_cast< int >( UI::SCREEN_SIZE.y ), "StarHuddle" );

	auto      full_inner_size = Vector2( UI::SCREEN_SIZE.x - ( UI::MARGIN * 2 ), UI::SCREEN_SIZE.y - ( UI::MARGIN * 2 ) );

	Vector2   filter_bar_size = Vector2( full_inner_size.x , 50 );
	Vector2   detail_bar_size = Vector2( 200.f, full_inner_size.y - filter_bar_size.y - UI::MARGIN);
	Vector2   asset_grid_size = Vector2( full_inner_size.x - detail_bar_size.x - UI::MARGIN, full_inner_size.y - filter_bar_size.y - UI::MARGIN );

	Vector2   cursor_position = Vector2( UI::MARGIN, UI::MARGIN );
	FilterBar filter_bar      = FilterBar( cursor_position, filter_bar_size );

	cursor_position           = Vector2( UI::MARGIN, UI::MARGIN + filter_bar_size.y + UI::MARGIN ); // Cursor Repositions
	AssetGrid asset_grid      = AssetGrid( cursor_position, asset_grid_size );

	cursor_position           = Vector2( asset_grid_size.x + ( UI::MARGIN * 2 ), filter_bar_size.y + ( UI::MARGIN * 2 ) ); // Cursor Repositions
	DetailBar detail_bar      = DetailBar( cursor_position, detail_bar_size );

	while (!WindowShouldClose())
	{
		// Update pass

		if( IsFileDropped() )
		{
			auto dropped_files = LoadDroppedFiles();

			for( unsigned int i = 0; i < dropped_files.count; i++ )
			{
				auto file_path = std::string( dropped_files.paths[ i ] );
				asset_manager.importFile( file_path );
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
		ClearBackground( UI::ACCENT1 );

		asset_grid.draw();
		filter_bar.draw();
		detail_bar.draw();

		EndDrawing();
	}

	RaylibCloseWindow();

	return 0;
}
