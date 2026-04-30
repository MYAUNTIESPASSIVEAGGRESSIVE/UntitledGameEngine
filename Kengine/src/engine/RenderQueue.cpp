#include "RenderQueue.h"
#include "graphics/materials/DXMaterial.h"
#include "physics/PhysicsManager.h"

RenderQueue* RenderQueue::_instance = NULL;

RenderQueue* RenderQueue::Instance()
{
	if (_instance == NULL) return _instance = new RenderQueue();

	return _instance;
}

bool RenderQueue::ComapreMaterial(GameObject* a, GameObject* b)
{
	return (a->GetObjectMaterial()->GetRenderOrder() > b->GetObjectMaterial()->GetRenderOrder()) ? true : false;
}

void RenderQueue::AddObject(GameObject* GO)
{
	RenderableObjects.insert(GO);

	if(GO->SimulatePhysics) PhysicsManager::Instance()->AddGameObject(GO);
}

void RenderQueue::RemoveObject(GameObject* GO)
{
	if (GO->SimulatePhysics) PhysicsManager::Instance()->RemoveGameObject(GO);
	RenderableObjects.erase(GO);
	delete GO;
}
