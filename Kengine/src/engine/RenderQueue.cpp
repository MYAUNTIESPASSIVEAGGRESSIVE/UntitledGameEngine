#include "RenderQueue.h"
#include "gameobjects/GameObject.h"
#include "graphics/materials/DXMaterial.h"

bool RenderQueue::ComapreMaterial(GameObject a, GameObject b)
{
	return (a.GetObjectMaterial()->GetRenderOrder() > b.GetObjectMaterial()->GetRenderOrder()) ? true : false;
}

void RenderQueue::AddObject(GameObject& GO)
{
	RenderableObjects.insert(GO);
}

void RenderQueue::RemoveObject(GameObject& GO)
{
	//auto it = RenderableObjects.find(GO);

	//if (it != RenderableObjects.end())
	//{
	//	RenderableObjects.erase(GO);
	//}

	RenderableObjects.erase(GO);
}
