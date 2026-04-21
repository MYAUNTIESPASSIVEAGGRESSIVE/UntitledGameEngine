#pragma once
#include <set>

class GameObject;

struct RenderQueue 
{
	std::set<GameObject> RenderableObjects;

	void AddObject(GameObject GO);

	void RemoveObject(GameObject GO);
};

