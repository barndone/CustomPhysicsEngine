#include "PhysObject.h"
#include "raylib.h"


using namespace glm;


void PhysObject::TickPhysics(float _fixedDelta)
{
	//	TODO integrate forces into velocity

	//	integrate velocity into position
	Position += Velocity * _fixedDelta;
}

void PhysObject::AddForce(vec2 _force)
{
	Forces += _force * (1.0f / Mass);
}

void PhysObject::Draw() const
{
	switch (Collider.Type)
	{
	case ShapeType::NONE:

		break;
	case ShapeType::CIRCLE:
		DrawCircleLines(Position.x, Position.y, Collider.CircleData.Radius, RED);
		break;
	case ShapeType::AABB:
		DrawPixel(Position.x, Position.y, RED);
		DrawRectangleLines(	Position.x - Collider.AABBData.Width / 2.0f, 
							Position.y - Collider.AABBData.Height / 2.0f, 
							Collider.AABBData.Width, Collider.AABBData.Height, RED);
		break;
	}
}


