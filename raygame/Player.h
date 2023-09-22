#pragma once

#include "raylib.h"
#include "glm/vec2.hpp"

class Player
{
public:
	glm::vec2 Position = {};

	Player();

	void Update();
};