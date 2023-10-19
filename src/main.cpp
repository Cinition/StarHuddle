#include "App.h"

#include "UI/Layout.h"

#include <raylib.h>

int WinMain(void)
{
	InitWindow( static_cast< int >( LAYOUT::SCREEN_SIZE.x ), static_cast< int >( LAYOUT::SCREEN_SIZE.y ), "StarHuddle" );

	App app;

	while (!WindowShouldClose())
	{
		app.update( GetFrameTime() );
		app.draw();
	}

	RaylibCloseWindow();

	return 0;
}
