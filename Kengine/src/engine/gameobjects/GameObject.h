#pragma once
#include "Object.h"
#include "engine/physics/Collision.h"
#include <memory>

class DXMaterial;

class DXMesh;

class GameObject :
	public Object
{
public:

	GameObject(std::string objectName, DXMesh* objectMesh, std::shared_ptr<DXMaterial> objMaterial, 
		ColliderType type, bool simulatePhysics);

	//GameObject() {};
	//GameObject(GameObject&&) {};

	//GameObject(const GameObject&) = delete;
	//GameObject& operator=(const GameObject&) = delete;

	~GameObject() {};

	DXMesh* GetObjectMesh() { return ObjectMesh; }
	std::shared_ptr<DXMaterial> GetObjectMaterial() { return ObjectMaterial; }

	bool SimulatePhysics;

	XMVECTOR velocity;

	float Mass = 10;

	void ApplyForce(XMVECTOR force, float deltaTime);

	void UpdateBody(float deltaTime);

	//Collider GetCollider() const { return collider; }

	virtual void Update() {};

private:

	//Collider collider;

	DXMesh* ObjectMesh;

	std::shared_ptr<DXMaterial> ObjectMaterial;
};

