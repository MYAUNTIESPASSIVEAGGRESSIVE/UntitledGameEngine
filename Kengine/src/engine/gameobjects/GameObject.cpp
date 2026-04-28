#include "GameObject.h"

GameObject::GameObject(std::string objName, DXMesh* objMesh, std::shared_ptr<DXMaterial> objMaterial, 
	ColliderType type, bool simulatePhysics) 
	: Object(objName)
{
	//collider = { type };
	SimulatePhysics = simulatePhysics;
	ObjectMesh = objMesh;
	ObjectMaterial = objMaterial;
}

void GameObject::ApplyForce(XMVECTOR force, float deltaTime)
{
	XMVECTOR acceleration = force * (1.0f / Mass);

	velocity = XMVectorAdd(velocity, acceleration * deltaTime);
}

void GameObject::UpdateBody(float deltaTime)
{
	transform.Translate(velocity * deltaTime);
}
