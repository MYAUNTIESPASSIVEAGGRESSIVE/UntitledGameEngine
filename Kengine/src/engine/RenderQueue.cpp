#include "RenderQueue.h"
#include "physics/PhysicsManager.h"

RenderQueue* RenderQueue::_instance = NULL;

RenderQueue* RenderQueue::Instance()
{
	if (_instance == NULL) return _instance = new RenderQueue();

	return _instance;
}

void RenderQueue::AddObject(GameObject* GO)
{
	RenderableObjects.push_back(GO);

	if(GO->SimulatePhysics) PhysicsManager::Instance()->AddGameObject(GO);
}

void RenderQueue::RemoveObject(GameObject* GO)
{
	if (GO->SimulatePhysics) PhysicsManager::Instance()->RemoveGameObject(GO);
	auto gameObject = std::find(RenderableObjects.begin(), RenderableObjects.end(), GO);
	if (gameObject != RenderableObjects.end())
	{
		RenderableObjects.erase(gameObject);
		GO->~GameObject();
	}
}
