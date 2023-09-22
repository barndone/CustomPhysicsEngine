#pragma once

#include "PhysObject.h"
#include <vector>
class BaseGame
{
protected:
	//	time since the last fixed update call
	float AccumulatedFixedTime = 0.0f;

	//	internal lifecycle events
	void virtual OnInit() {}

	void virtual OnTick() { }

	void virtual OnDraw() const { }

	void virtual OnExit() { }

	std::vector<class PhysObject*> PhysicsObjects;

	//	TODO: store a collection of PhysObjects
	//	TODO: during tickfixed, tick every physObject in that collection

public:
	//	default to 30 fps
	float TargetFixedStep = 1.0f / 30.0f;

	// default constructor - set up good defaults
	BaseGame();
	~BaseGame();
	//	initialize the game
	void Init();
	//	poll for input and process game logic
	void Tick();
	//	Tick any fixed update objects
	void TickFixed();
	//	drawing objects to screen
	void Draw() const;
	//	terminate -- clean up resources
	void Exit();
	//	returns true if we need to exit
	bool ShouldClose() const;
	//	return true if we are due for a fixed update
	bool ShouldTickFixed() const;
};