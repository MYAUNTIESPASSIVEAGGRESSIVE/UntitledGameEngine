#include "GameObject.h"

GameObject::GameObject(std::string objName, DXMesh* objMesh, DXMaterial* objMaterial) 
	: Object(objName)
{
	ObjectMesh = objMesh;
	ObjectMaterial = objMaterial;
}
