/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "DemoGame.h"

int main()
{
	BaseGame* game = new DemoGame();

	game->Init();

	while (!game->ShouldClose())
	{
		game->Tick();

		if (game->ShouldTickFixed())
		{
			game->TickFixed();
		}
		game->Draw();
	}

	game->Exit();

	return 0;
}