#pragma once
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "engine/gameobjects/Transform.h"
#include <string>
using namespace DirectX;

class GameObject;

enum ColliderType
{
	SPHERE,
	BOX,
	NONE
};

struct SphereCollider
{
	Transform transform;

	float radius;

	SphereCollider(Transform circle = { 0.0f, 0.0f, 0.0f }, float rad = 0)
		: transform(circle), radius(rad)
	{
		//boundingSphere.Radius = radius;
	}

	void UpdatePosition(Transform objectpos)
	{
		transform = objectpos;
		//boundingSphere.Center = { XMVectorGetX(transform.position),XMVectorGetY(transform.position),XMVectorGetZ(transform.position) };
	}

	//BoundingSphere boundingSphere;
};


//struct BoxCollider
//{
//	Transform transform;
//
//	float minX;
//	float maxX;
//	float minY;
//	float maxY;
//	float minZ;
//	float maxZ;
//
//	BoxCollider(Transform transform = {0,0,0})
//		:transform(transform)
//	{
//		UpdatePosition(transform);
//	};
//
//	void UpdatePosition(Transform objectpos)
//	{
//		transform = objectpos;
//		maxX = XMVectorGetX(XMVectorAdd(transform.position, transform.scale));
//		maxY = XMVectorGetY(XMVectorAdd(transform.position, transform.scale));
//		maxZ = XMVectorGetY(XMVectorAdd(transform.position, transform.scale));
//
//	}
//
//};

struct Raycast
{
	Transform raypos;

	XMVECTOR direction;

	float distance;

	Raycast(Transform transform = { 0,0,0 }, XMVECTOR dir = { 0,0,0 }, float dist = 0)
		: raypos(transform), direction(dir), distance(dist) 
	{
	}

	void UpdateValues(Transform transform)
	{
		raypos = transform;
	}
};

struct Collider
{
	ColliderType Type;

	SphereCollider sphereCollider;

	//BoxCollider boxCollider;

	std::string previousCollidedObject = "";

	Collider(ColliderType type = NONE, Transform transform = {0,0,0}, float radius = 0.0f)
		:Type(type)
	{
		if (Type == ColliderType::BOX)
		{
			//boxCollider = { transform };
		}
		else if (Type == ColliderType::SPHERE)
		{
			sphereCollider = { transform, radius };
		}
	}

	void UpdatePosition(Transform objectpos)
	{
		//if (Type == ColliderType::BOX) boxCollider.UpdatePosition(objectpos);

		if (Type == ColliderType::SPHERE) sphereCollider.UpdatePosition(objectpos);
	}
};

class Collision
{
public:

	static bool OnSphereCollide(SphereCollider c1, SphereCollider c2);

	//static bool OnBoxCollide(BoxCollider box1, BoxCollider box2);

	//static bool OnBoxVCircleCollide(BoxCollider box, SphereCollider circle);

	static bool OnCollide(GameObject* obj1, GameObject* obj2);

	static bool RayCastCheck(Raycast point, Collider collider);
};


