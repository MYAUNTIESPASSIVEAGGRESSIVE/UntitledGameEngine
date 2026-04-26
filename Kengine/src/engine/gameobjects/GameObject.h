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

	XMVECTOR velocity;

	float Mass = 10;

	void ApplyForce(XMVECTOR force, float deltaTime);

	void UpdateBody(float deltaTime);

	//Collider GetCollider() const { return collider; }

protected:

	void Update() {};

private:

	//Collider collider;

	DXMesh* ObjectMesh;

	DXMaterial* ObjectMaterial;
};

