#pragma once
#include "Object.h"
#include "engine/physics/Collision.h"

class DXMaterial;

class DXMesh;

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

	XMVECTOR velocity;

	float Mass = 10;

	void ApplyForce(XMVECTOR force, float deltaTime);

	void UpdateBody(float deltaTime);

protected:

	void Update() {};

private:

	DXMesh* ObjectMesh;

	DXMaterial* ObjectMaterial;
};

