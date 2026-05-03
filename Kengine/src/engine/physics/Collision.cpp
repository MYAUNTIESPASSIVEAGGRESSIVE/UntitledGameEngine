#include "Collision.h"
#include "engine/gameobjects/GameObject.h"

// circle vs circle collision check
bool Collision::OnSphereCollide(SphereCollider c1, SphereCollider c2)
{
	float dx = XMVectorGetX(c2.transform.position) - XMVectorGetX(c1.transform.position);
	float dy = XMVectorGetY(c2.transform.position) - XMVectorGetY(c1.transform.position);
	float dz = XMVectorGetZ(c2.transform.position) - XMVectorGetZ(c1.transform.position);

	float distance = sqrt((dx * dx) + (dy * dy) + (dz * dz));

	return distance <= c1.radius + c2.radius ? true : false;
}

// AABB vs AABB collision check
//bool Collision::OnBoxCollide(BoxCollider box1, BoxCollider box2)
//{
//	return box1.boundingBox.Intersects(box2.boundingBox);
//}
//
//// Box vs Cricle Collision
//bool Collision::OnBoxVCircleCollide(BoxCollider box, SphereCollider circle)
//{
//	return box.boundingBox.Intersects(circle.boundingSphere);
//}

bool Collision::OnCollide(GameObject* obj1, GameObject* obj2)
{
	if(obj1->collider.Type == ColliderType::SPHERE && obj2->collider.Type == ColliderType::SPHERE)
	{
		return OnSphereCollide(obj1->collider.sphereCollider, obj2->collider.sphereCollider);
	}
	//else
	//{
	//	if (obj1->collider.Type == ColliderType::BOX) return OnBoxVCircleCollide(obj1->collider.boxCollider, obj2->collider.sphereCollider);
	//	else return OnBoxVCircleCollide(obj2->collider.boxCollider, obj1->collider.sphereCollider);
	//}
}

// ------- Modified to work around assert error! -------
//-------------------------------------------------------------------------------------
// DirectXCollision.inl -- C++ Collision Math library
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkID=615560
//-------------------------------------------------------------------------------------
bool Collision::RayCastCheck(Raycast point, Collider collider)
{
	XMVECTOR vRadius = XMVectorReplicate(collider.sphereCollider.radius);

	// l is the vector from the ray origin to the center of the sphere.
	XMVECTOR l = XMVectorSubtract(collider.sphereCollider.transform.position, point.raypos.position);

	// s is the projection of the l onto the ray direction.
	XMVECTOR s = XMVector3Dot(l, point.direction);

	XMVECTOR l2 = XMVector3Dot(l, l);

	XMVECTOR r2 = XMVectorMultiply(vRadius, vRadius);

	// m2 is squared distance from the center of the sphere to the projection.
	XMVECTOR m2 = XMVectorNegativeMultiplySubtract(s, s, l2);

	XMVECTOR NoIntersection;

	// If the ray origin is outside the sphere and the center of the sphere is
	// behind the ray origin there is no intersection.
	NoIntersection = XMVectorAndInt(XMVectorLess(s, XMVectorZero()), XMVectorGreater(l2, r2));

	// If the squared distance from the center of the sphere to the projection
	// is greater than the radius squared the ray will miss the sphere.
	NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(m2, r2));

	// The ray hits the sphere, compute the nearest intersection point.
	XMVECTOR q = XMVectorSqrt(XMVectorSubtract(r2, m2));
	XMVECTOR t1 = XMVectorSubtract(s, q);
	XMVECTOR t2 = XMVectorAdd(s, q);

	XMVECTOR OriginInside = XMVectorLessOrEqual(l2, r2);
	XMVECTOR t = XMVectorSelect(t1, t2, OriginInside);

	if (XMVector4NotEqualInt(NoIntersection, XMVectorTrueInt()))
	{
		// Store the x-component to *pDist.
		XMStoreFloat(&point.distance, t);
		return true;
		printf("collided");
	}

	return false;
}

