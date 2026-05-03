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

	/// <summary>
	/// Game Object Constuctor
	/// </summary>
	/// <param name="Object's Name"></param>
	/// <param name="Object's Tag"></param>
	/// <param name="Object's Mesh"></param>
	/// <param name="Object's Material"></param>
	/// <param name="Collider Type (ONLY USE SPHERE AND NONE)"></param>
	/// <param name="Does the object SimulatePhysics"></param>
	/// <param name="How large is the collider's radius"></param>
	GameObject(std::string objectName, std::string Tag, DXMesh* objectMesh, DXMaterial* objMaterial, 
		ColliderType type, bool simulatePhysics = true, float circlerad = 1);

	~GameObject();

	DXMesh* GetObjectMesh() { return ObjectMesh; }
	DXMaterial* GetObjectMaterial() { return ObjectMaterial; }

	bool SimulatePhysics;

	XMVECTOR velocity;

	float Mass = 10;

	void DestoryObject();

	/// <summary>
	/// Applies a force as a vector
	/// </summary>
	/// <param name="force vector (determines direction)"></param>
	/// <param name="deltaTime"></param>
	void ApplyForce(XMVECTOR force, float deltaTime);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="deltaTime"></param>
	void UpdateBody(float deltaTime);

	virtual void Update() {};

	Collider collider;

private:


	DXMesh* ObjectMesh;

	DXMaterial* ObjectMaterial;
};

