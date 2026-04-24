#pragma once
#include "Collision.h"
#include <vector>
#include "RigidBody.h"
#include "engine/Timer.h"

class PhysicsManager
{
public:
	XMVECTOR Gravity{ 0, -9.81f, 0 };

	void UpdatePhysics();

private:

	std::vector<RigidBody*> physicsObjects;
};

