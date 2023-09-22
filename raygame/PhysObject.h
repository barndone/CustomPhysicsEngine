#pragma once

//	#include "glm/glm.hpp"	//	heavy handed --EVERYTHING
//	just include what we need
#include "glm/vec2.hpp"
#include "glm/glm.hpp"
#include "Shape.h"

class PhysObject
{
	//	accumulated forces applied to a physics object
	//	that will be integrated into velocity on the next tick physics
	glm::vec2 Forces = {};

public:
	//	position
	glm::vec2 Position = {};
	//	velocity
	glm::vec2 Velocity = {};

	Shape Collider;

	float Mass = 1.0f;

	float Drag = 0.5f;

	bool UseGravity = true;
	bool IsStatic = false;

	void TickPhysics(float _fixedDelta);
	void AddForce(glm::vec2 _force);
	void AddAcceleration(glm::vec2 _acceleration);
	void AddImpulse(glm::vec2 _impulse);
	void AddVelocity(glm::vec2 _velocity);

	void Draw() const;

	glm::vec2 GetMomentum() const;
};

void ResolvePhysObjects(PhysObject& _left, PhysObject& _right, float _elasticity, glm::vec2 _normal, float _pen);

float ResolveCollision(const glm::vec2& _posA, const glm::vec2& _velA, float _massA,
	const glm::vec2& _posB, const glm::vec2& _velB, float _massB, float _elasticity, const glm::vec2 _normal);