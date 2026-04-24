#pragma once
#include <DirectXMath.h>
using namespace DirectX;

enum ColliderType
{
	SPHERE,
	BOX
};

struct Collider
{
	ColliderType Type;
};

struct SphereCollider : Collider
{
	XMVECTOR circleVector;

	float radius;

	SphereCollider(XMVECTOR circle, float rad)
		: circleVector(circle), radius(rad) { }
};


struct BoxCollider : Collider
{
	XMVECTOR min;
	XMVECTOR max;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	BoxCollider(XMVECTOR amin, XMVECTOR amax)
		:min(amin), max(amax)
	{
		minX = XMVectorGetX(min);
		maxX = XMVectorGetX(max);

		minY = XMVectorGetY(min);
		maxY = XMVectorGetY(max);

		minZ = XMVectorGetZ(min);
		maxZ = XMVectorGetZ(max);
	};
};


static class Collision
{
public:

	static bool OnSphereCollide(SphereCollider c1, SphereCollider c2);

	static bool OnBoxCollide(BoxCollider box1, BoxCollider box2);

	static bool OnBoxVCircleColldier(BoxCollider box, SphereCollider circle);

	//static bool RayCast(XMVECTOR point, Collider collider);
};


