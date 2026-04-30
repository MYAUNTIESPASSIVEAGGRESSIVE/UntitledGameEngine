#include "GameObject.h"
#include "graphics/DXRenderer.h"

GameObject::GameObject(std::string objectName, DXMesh* objectMesh, DXMaterial* objMaterial, ColliderType type, bool simulatePhysics, float circlerad)
	:Object(objectName)
{
	ObjectMesh = objectMesh;
	ObjectMaterial = objMaterial;
	SimulatePhysics = simulatePhysics;

	if (type == ColliderType::BOX || ColliderType::SPHERE)
	{
		collider = { type, transform, circlerad };
	}
	else
	{
		collider = { type, transform, circlerad};
	}
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

void GameObject::DestoryObject()
{
	RenderQueue::Instance()->RemoveObject(this);
}


GameObject::~GameObject()
{
	ObjectMesh = nullptr;
	ObjectMaterial = nullptr;
}