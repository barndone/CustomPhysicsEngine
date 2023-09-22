#include "DemoGame.h"
#include "PhysObject.h"

void DemoGame::OnInit()
{
	// let's initialize a PhysObject
	PhysicsObjects.emplace_back(new PhysObject());
	PhysicsObjects.back()->Position = { 200, 200 };
	PhysicsObjects.back()->Collider.Type = ShapeType::CIRCLE;
	PhysicsObjects.back()->Collider.CircleData = Circle{ 10 };

	PhysicsObjects.emplace_back(new PhysObject());
	PhysicsObjects.back()->Position = { 225, 200 };
	PhysicsObjects.back()->Collider.Type = ShapeType::AABB;
	PhysicsObjects.back()->Collider.AABBData = AABB{ 10, 10 };
}

void DemoGame::OnTick()
{}
