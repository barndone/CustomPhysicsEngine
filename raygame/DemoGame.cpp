#include "DemoGame.h"
#include "PhysObject.h"
#include "raylib.h"

void DemoGame::OnInit()
{
	// let's initialize a PhysObject
	PhysicsObjects.emplace_back(new PhysObject());
	PhysicsObjects.back()->Position = { 200, 200 };
	PhysicsObjects.back()->UseGravity = false;
	//PhysicsObjects.back()->Collider.Type = ShapeType::AABB;
	//PhysicsObjects.back()->Collider.AABBData = AABB{ 10,10 };
	PhysicsObjects.back()->Collider.Type = ShapeType::CIRCLE;
	PhysicsObjects.back()->Collider.CircleData = Circle{ 20 };

	PhysicsObjects.emplace_back(new PhysObject());
	PhysicsObjects.back()->Position = { 200, 200 };
	PhysicsObjects.back()->UseGravity = false;
	PhysicsObjects.back()->IsStatic = true;
	//PhysicsObjects.back()->Collider.Type = ShapeType::AABB;
	//PhysicsObjects.back()->Collider.AABBData = AABB{ 20,20 };
	PhysicsObjects.back()->Collider.Type = ShapeType::CIRCLE;
	PhysicsObjects.back()->Collider.CircleData = Circle{10};

}

void DemoGame::OnTick()
{
	PhysObject* player = PhysicsObjects[0];

	//	move up
	if (IsKeyPressed(KEY_W))
	{
		//	-
		player->AddImpulse({0, -100});
	}

	//	move down
	if (IsKeyPressed(KEY_S))
	{
		//	+
		player->AddImpulse({ 0, 100 });
	}

	//	move left
	if (IsKeyPressed(KEY_A))
	{
		// -
		player->AddImpulse({ -100, 0 });
	}

	//	move right
	if (IsKeyPressed(KEY_D))
	{
		// +
		player->AddImpulse({ 100, 0 });
	}
}
