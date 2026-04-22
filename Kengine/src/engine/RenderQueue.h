#pragma once
#include <set>

class GameObject;

struct RenderQueue 
{
	bool ComapreMaterial(GameObject a, GameObject b);

	std::set<GameObject, decltype(ComapreMaterial)*> RenderableObjects;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="GO"></param>
	void AddObject(GameObject& GO);

	void RemoveObject(GameObject& GO);
};

