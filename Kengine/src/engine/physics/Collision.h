#pragma once
#include <DirectXMath.h>
using namespace DirectX;

enum ColliderType
{
	SPHERE,
	BOX
};

struct SphereCollider
{
	XMVECTOR circleVector;

	float radius;

	SphereCollider(XMVECTOR circle, float rad)
		: circleVector(circle), radius(rad)
	{ }
};


struct BoxCollider
{
	XMVECTOR minvec;
	XMVECTOR maxvec;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	BoxCollider(XMVECTOR amin, XMVECTOR amax)
		:minvec(amin), maxvec(amax)
	{
		minX = XMVectorGetX(minvec);
		maxX = XMVectorGetX(maxvec);

		minY = XMVectorGetY(minvec);
		maxY = XMVectorGetY(maxvec);

		minZ = XMVectorGetZ(minvec);
		maxZ = XMVectorGetZ(maxvec);
	};
};

struct Collider
{
	//XMVECTOR ColliderHeight;
	//XMVECTOR ColliderWidth;

	ColliderType Type;

	//SphereCollider sphereCollider;

	//BoxCollider boxCollider;

	Collider(ColliderType type)
		:Type(type)
	{
		//if (Type == ColliderType::BOX)
		//{
		//	boxCollider = {};
		//}
		//else if (Type == ColliderType::SPHERE)
		//{
		//	sphereCollider = {};
		//}
	}
};

class Collision
{
public:

	static bool OnSphereCollide(SphereCollider c1, SphereCollider c2);

	static bool OnBoxCollide(BoxCollider box1, BoxCollider box2);

	static bool OnBoxVCircleCollide(BoxCollider box, SphereCollider circle);

	//static bool RayCast(XMVECTOR point, Collider collider);
};


