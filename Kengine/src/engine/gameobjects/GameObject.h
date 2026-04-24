#pragma once
#include "Object.h"
#include "engine/physics/Collision.h"

class DXMaterial;

class DXMesh;

struct RigidBody
{
	XMVECTOR position;
	XMVECTOR velocity;
	float Mass;

	RigidBody(XMVECTOR pos = {0.0f,0.0f,0.0f}, XMVECTOR vel = {0.0f, 0.0f, 0.0f}, float m = 0.0f)
		:position(pos), velocity(vel), Mass(m) { }
	
	void ApplyForce(XMVECTOR force, float deltaTime)
	{
		XMVECTOR acceleration = force * (1.0f / Mass);

		velocity += acceleration * deltaTime;
	}

	void UpdateBody(float deltaTime)
	{
		position += velocity * deltaTime;
	}
};

class GameObject :
	public Object
{
public:

	GameObject(std::string objectName, DXMesh* objectMesh, DXMaterial* objMaterial, 
		ColliderType type, bool simulatePhysics);

	DXMesh* GetObjectMesh() { return ObjectMesh; }
	DXMaterial* GetObjectMaterial() { return ObjectMaterial; }

	bool SimulatePhysics;

	Collider Collider;

	RigidBody rigidBody;

private:

	DXMesh* ObjectMesh;

	DXMaterial* ObjectMaterial;
};

