#pragma once

//	#include "glm/glm.hpp"	//	heavy handed --EVERYTHING
//	just include what we need
#include "glm/vec2.hpp"
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
	void TickPhysics(float fixedDelta);
	void AddForce(glm::vec2 force);

	void Draw() const;
};