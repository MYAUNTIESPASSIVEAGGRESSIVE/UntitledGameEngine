#include "GameObject.h"

GameObject::GameObject(std::string objName, DXMesh* objMesh, DXMaterial* objMaterial)
	:objectName(objName), ObjectMesh(objMesh), ObjectMaterial(objMaterial)
{

}

void GameObject::SetParent(GameObject* parent)
{

}

DXMesh* GameObject::SetObjectMesh(DXMesh* inMesh)
{
		return nullptr;
}
