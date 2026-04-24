#pragma once
#include "Collision.h"
#include <vector>
#include "engine/gameobjects/GameObject.h"

class PhysicsManager
{
public:
	static PhysicsManager* Instance();

	XMVECTOR Gravity{ 0, -9.81f, 0 };

	void UpdatePhysics(float deltaTime)
	{
		for (auto& GO : physicsObjects)
		{
			GO.transform.position += GO.rigidBody.velocity * deltaTime;
		}
	}

	void AddGameObject(GameObject& GO)
	{
		physicsObjects.push_back(GO);
	}

private:

	static PhysicsManager* _instance;

	std::vector<GameObject> physicsObjects;

	PhysicsManager() {};
	~PhysicsManager()
	{
		delete _instance;
		_instance = NULL;
	}
};

