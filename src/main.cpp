#include "UI/MainScreen.h"

#include "raylib.h"

int WinMain(void)
{
	InitWindow(800, 450, "StarHuddle");
	
	MainScreen main_screen;

	while (!WindowShouldClose())
	{
		main_screen.render();
	}

	CloseWindow();

	return 0;
}
