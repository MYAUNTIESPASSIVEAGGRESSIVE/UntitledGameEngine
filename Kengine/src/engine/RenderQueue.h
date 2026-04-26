#pragma once
#include <set>

class GameObject;

struct RenderQueue 
{
	bool ComapreMaterial(GameObject* a, GameObject* b);

	std::set<GameObject*, decltype(ComapreMaterial)*> RenderableObjects;


	/// <summary>
	/// Puts the game object within the render queue
	/// if has physics enabled then it also adds it to the physics object list
	/// </summary>
	/// <param name="Game Object"></param>
	void AddObject(GameObject* GO);

	void RemoveObject(GameObject* GO);
};

