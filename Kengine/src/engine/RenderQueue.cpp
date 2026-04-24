#include "RenderQueue.h"
#include "gameobjects/GameObject.h"
#include "graphics/materials/DXMaterial.h"
#include "physics/PhysicsManager.h"

bool RenderQueue::ComapreMaterial(GameObject a, GameObject b)
{
	return (a.GetObjectMaterial()->GetRenderOrder() > b.GetObjectMaterial()->GetRenderOrder()) ? true : false;
}

void RenderQueue::AddObject(GameObject& GO)
{
	RenderableObjects.insert(GO);

	if(GO.SimulatePhysics) PhysicsManager::Instance()->AddGameObject(GO);
}

void RenderQueue::RemoveObject(GameObject& GO)
{

	RenderableObjects.erase(GO);
}
