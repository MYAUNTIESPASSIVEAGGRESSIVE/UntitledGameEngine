#include "GameObject.h"

GameObject::GameObject(std::string objName, DXMesh* objMesh, DXMaterial* objMaterial, 
	ColliderType type, bool simulatePhysics) 
	: Object(objName)
{
	Collider.Type = type;
	SimulatePhysics = simulatePhysics;
	ObjectMesh = objMesh;
	ObjectMaterial = objMaterial;

	rigidBody = { transform.position, XMVECTOR{ 0.0f, 0.0f, 0.0f}, 10.0f };
}
