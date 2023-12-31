//	matching header for source file comes first
//	std library
//	other libraries
//	project specific libraries
//	other project-specific dependencies (i.e., gameplay)

#include "BaseGame.h"

#include "raylib.h"
#include <unordered_map>
#include "PhysObject.h"

#include "EnumUtils.h"

using CollisionFunc = bool(*)(const glm::vec2&, const Shape&, const glm::vec2&, const Shape&);
using DepenetrationFunc = glm::vec2(*)(const glm::vec2&, const Shape&, const glm::vec2&, const Shape&, float&);
using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;
using DepenetrationMap = std::unordered_map<ShapeType, DepenetrationFunc>;

CollisionMap collisionCheckers;
DepenetrationMap collisionDepenetrators;

BaseGame::BaseGame() 
{

}

BaseGame::~BaseGame()
{
	for (auto pObj : PhysicsObjects)
	{
		delete pObj;
	}

	PhysicsObjects.clear();
}

void BaseGame::Init() 
{
	OnInit();

	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	collisionCheckers[ShapeType::CIRCLE | ShapeType::CIRCLE]	= CheckCircleCircle;
	collisionCheckers[ShapeType::AABB | ShapeType::AABB]		= CheckAABBAABB;
	collisionCheckers[ShapeType::CIRCLE | ShapeType::AABB]		= CheckCircleAABB;

	collisionDepenetrators[ShapeType::CIRCLE | ShapeType::CIRCLE]	= DepenetrateCircleCircle;
	collisionDepenetrators[ShapeType::AABB | ShapeType::AABB]		= DepenetrateAABBAABB;
	collisionDepenetrators[ShapeType::CIRCLE | ShapeType::AABB]		= DepenetrateCircleAABB;

	SetTargetFPS(60);
}

void BaseGame::Tick() 
{
	AccumulatedFixedTime += GetFrameTime();
	OnTick();
}

void BaseGame::TickFixed()
{
	for (auto PhysObj : PhysicsObjects)
	{
		PhysObj->TickPhysics(TargetFixedStep);
	}
	AccumulatedFixedTime -= TargetFixedStep;

	for (auto& i : PhysicsObjects)
	{
		for (auto& j : PhysicsObjects)
		{
			if (&i == &j) { continue; }
			
			PhysObject* left = i;
			PhysObject* right = j;
	
			if (i->Collider.Type > j->Collider.Type)
			{
				left = j;
				right = i;
			}
	
			ShapeType pairType = left->Collider.Type | right->Collider.Type;
			bool inCollision = collisionCheckers[pairType](left->Position, left->Collider,
															right->Position, right->Collider);
			if (inCollision)
			{
				float pen = 0.0f;
				glm::vec2 normal = collisionDepenetrators[pairType](left->Position, left->Collider, right->Position, right->Collider, pen);
				
				ResolvePhysObjects(*left, *right, 1.0f, normal, pen);
			}
		}
	}
}

void BaseGame::Draw() const 
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText("CONTROLS:", 20, 10, 15, BLACK);
	DrawText("Left click to spawn a non-static Circle", 25, 26, 10, BLACK);
	DrawText("Right click to spawn a non-static AABB (Rect)", 25, 37, 10, BLACK);
	DrawText("Hold shift while clicking to spawn a static object", 25, 48, 10, BLACK);

	for (auto PhysObj : PhysicsObjects)
	{
		PhysObj->Draw();
	}

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