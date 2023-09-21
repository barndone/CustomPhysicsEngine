//	matching header for source file comes first
//	std library
//	other libraries
//	project specific libraries
//	other project-specific dependencies (i.e., gameplay)

#include "BaseGame.h"
#include "raylib.h"

BaseGame::BaseGame() 
{
}

void BaseGame::Init() 
{
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
}

void BaseGame::Tick() 
{
	AccumulatedFixedTime += GetFrameTime();
	OnTick();
}

void BaseGame::TickFixed()
{
	AccumulatedFixedTime -= TargetFixedStep;
}

void BaseGame::Draw() const 
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText("BOTTOM TEXT", 190, 200, 20, LIGHTGRAY);
	OnDraw();
	EndDrawing();
}

void BaseGame::Exit() 
{
	CloseWindow();
}

bool BaseGame::ShouldClose() const
{
	return WindowShouldClose();
}

bool BaseGame::ShouldTickFixed() const
{
	return AccumulatedFixedTime >= TargetFixedStep;
}