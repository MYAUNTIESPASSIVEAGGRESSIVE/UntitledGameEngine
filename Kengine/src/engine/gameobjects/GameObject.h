#pragma once
#include "Object.h"
#include "engine/physics/Collision.h"

class DXMaterial;

class DXMesh;

class DXRenderer;

class GameObject :
	public Object
{
public:

	GameObject(std::string objectName, DXMesh* objectMesh, DXMaterial* objMaterial, 
		ColliderType type, bool simulatePhysics = true, float circlerad = 1);

	~GameObject();

	DXMesh* GetObjectMesh() { return ObjectMesh; }
	DXMaterial* GetObjectMaterial() { return ObjectMaterial; }

	bool SimulatePhysics;

	XMVECTOR velocity;

	float Mass = 10;

	void DestoryObject();

	void ApplyForce(XMVECTOR force, float deltaTime);

	void UpdateBody(float deltaTime);

	virtual void Update() {};

	Collider collider;

private:


	DXMesh* ObjectMesh;

	DXMaterial* ObjectMaterial;
};

