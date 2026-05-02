#pragma once
#include <set>
#include <vector>
#include <memory>
#include "gameobjects/GameObject.h"
#include "graphics/materials/DXMaterial.h"
#include "gameobjects/DirectionalLightObject.h"
#include "gameobjects/PointLightObject.h"
#include <DirectXColors.h>

class RenderQueue
{
public:

	static RenderQueue* Instance();

	//std::set<GameObject*, decltype()> RenderableObjects;

	std::vector<GameObject*> RenderableObjects;

	XMVECTOR ambientLightColour = { 0,0,0 };
	DirectionalLightObject* directionalLight;
	PointLight pointLights[MAX_POINT_LIGHTS];

	/// <summary>
	/// Puts the game object within the render queue
	/// if has physics enabled then it also adds it to the physics object list
	/// </summary>
	/// <param name="Game Object"></param>
	void AddObject(GameObject* GO);

	void RemoveObject(GameObject* GO);

private:

	static RenderQueue* _instance;

	RenderQueue() {};
	~RenderQueue()
	{
		delete _instance;
		_instance = NULL;
	}
};

