#pragma once

//	#include "glm/glm.hpp"	//	heavy handed --EVERYTHING
//	just include what we need
#include "glm/vec2.hpp"

using namespace glm;

class PhysObject
{
public:
	//	position
	vec2 Position = {};
	//	velocity
	vec2 Velocity = {};

	void TickPhysics(float fixedDelta);
};