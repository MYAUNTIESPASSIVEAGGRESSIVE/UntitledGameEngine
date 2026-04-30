#pragma once
#include <DirectXMath.h>
#include "engine/gameobjects/Transform.h"
using namespace DirectX;

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

	SphereCollider(Transform circle = {0.0f, 0.0f, 0.0f}, float rad = 0)
		: transform(circle), radius(rad){ }

	void UpdatePosition(Transform objectpos)
	{
		transform = objectpos;
	}
};


struct BoxCollider
{
	Transform transform;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	BoxCollider(Transform transform = {0,0,0})
		:transform(transform)
	{
		UpdatePosition(transform);
	};

	void UpdatePosition(Transform objectpos)
	{
		transform = objectpos;

		minX = XMVectorGetX(XMVectorSubtract(transform.position, transform.scale));
		maxX = XMVectorGetX(XMVectorAdd(transform.position, transform.scale));

		minY = XMVectorGetY(XMVectorSubtract(transform.position, transform.scale));
		maxY = XMVectorGetY(XMVectorAdd(transform.position, transform.scale));

		minZ = XMVectorGetY(XMVectorSubtract(transform.position, transform.scale));
		maxZ = XMVectorGetY(XMVectorAdd(transform.position, transform.scale));
	}
};

struct Collider
{
	ColliderType Type;

	SphereCollider sphereCollider;

	BoxCollider boxCollider;

	Collider(ColliderType type = NONE, Transform transform = {0,0,0}, float radius = 0.0f)
		:Type(type)
	{
		if (Type == ColliderType::BOX)
		{
			boxCollider = { transform };
		}
		else if (Type == ColliderType::SPHERE)
		{
			sphereCollider = { transform, radius };
		}
	}

	void UpdatePosition(Transform objectpos)
	{
		if (Type == ColliderType::BOX) boxCollider.UpdatePosition(objectpos);

		if (Type == ColliderType::SPHERE) sphereCollider.UpdatePosition(objectpos);
	}
};

class Collision
{
public:

	static bool OnSphereCollide(SphereCollider c1, SphereCollider c2);

	static bool OnBoxCollide(BoxCollider box1, BoxCollider box2);

	static bool OnBoxVCircleCollide(BoxCollider box, SphereCollider circle);

	static bool OnCollide(Collider obj1, Collider obj2);

	//static bool RayCast(XMVECTOR point, Collider collider);
};


