#pragma once
#include <set>
#include "gameobjects/GameObject.h"

struct RenderQueue 
{
	bool ComapreMaterial(GameObject* a, GameObject* b);

	static std::set<GameObject*, decltype(ComapreMaterial)*> RenderableObjects;


	/// <summary>
	/// Puts the game object within the render queue
	/// if has physics enabled then it also adds it to the physics object list
	/// </summary>
	/// <param name="Game Object"></param>
	static void AddObject(GameObject* GO);

	static void RemoveObject(GameObject* GO);
};

