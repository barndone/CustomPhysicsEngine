#pragma once

#include "BaseGame.h"

class DemoGame : public BaseGame
{
protected:
	void virtual OnInit() override;
	void virtual OnTick() override;
};
