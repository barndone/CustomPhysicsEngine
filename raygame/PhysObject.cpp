#include "PhysObject.h"
#include "raylib.h"


using namespace glm;


void PhysObject::TickPhysics(float _fixedDelta)
{

	if (UseGravity) { AddAcceleration({ 0, 9 }); }
	//	integrate forces into velocity
	Velocity += Forces * _fixedDelta;
	//	clear out forces vector
	Forces = {};
	//	apply drag
	Velocity *= 1.0f - (_fixedDelta * Drag);
	//	integrate velocity into position
	Position += Velocity * _fixedDelta;
}

void PhysObject::AddForce(vec2 _force)
{
	Forces += _force * (1.0f / Mass);
}

void PhysObject::AddAcceleration(glm::vec2 _acceleration)
{
	Forces += _acceleration;
}

void PhysObject::AddImpulse(glm::vec2 _impulse)
{
	Velocity += _impulse * (1.0f / Mass);
}

void PhysObject::AddVelocity(glm::vec2 _velocity)
{
	Velocity += _velocity;
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

glm::vec2 PhysObject::GetMomentum() const
{
	return Velocity * Mass;
}

void ResolvePhysObjects(PhysObject& _left, PhysObject& _right, float _elasticity, glm::vec2 _normal, float _pen)
{
	//	calculate impulse magnitude
	float impulseMag = ResolveCollision(_left.Position, _left.Velocity, _left.Mass, 
										_right.Position, _right.Velocity, _right.Mass, _elasticity, _normal);
	//	apply impulses to both objects and separate them
	glm::vec2 mtv = _normal * _pen;




	glm::vec2 impulse = _normal * impulseMag;

	if (!_left.IsStatic)
	{
		_left.Position -= mtv;
		_left.AddImpulse(-impulse);
	}

	if (!_right.IsStatic)
	{
		_right.Position += mtv;
		_right.AddImpulse(impulse);
	}

}

float ResolveCollision(const glm::vec2& _posA, const glm::vec2& _velA, float _massA, const glm::vec2& _posB, const glm::vec2& _velB, float _massB, float _elasticity, const glm::vec2 _normal)
{	
	//	calculate the relative velocity
	glm::vec2 relVel = _velB - _velA;

	//	calc the impulse magnitude
	float impulseMag = 
		//	determine how much the relative velocity aligns with the collision normal
		glm::dot(-(1.0f + _elasticity) * relVel, _normal) / 
		//	account for the mass of each object (and how much it aligns with the collision normal)
		glm::dot(_normal, _normal * ((1.0f / _massA) + (1.0f / _massB)));

	//	return the impulse magnitude
	return impulseMag;
}


