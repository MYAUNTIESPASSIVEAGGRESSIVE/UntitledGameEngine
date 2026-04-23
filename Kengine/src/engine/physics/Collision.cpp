#include "Collision.h"

// circle vs circle collision check
bool Collision::OnCircleCollide(DirectX::XMVECTOR c1, DirectX::XMVECTOR c2, float c1r, float c2r)
{
	float dx = DirectX::XMVectorGetX(c2) - DirectX::XMVectorGetX(c1);
	float dy = DirectX::XMVectorGetY(c2) - DirectX::XMVectorGetY(c1);

	float distance = sqrt((dx * dx) + (dy * dy));

	return distance <= c1r + c2r ? true : false;
}

// AABB vs AABB collision check
bool Collision::OnBoxCollide(DirectX::XMVECTOR amin, DirectX::XMVECTOR amax, DirectX::XMVECTOR bmin, DirectX::XMVECTOR bmax)
{
	BoxCollider box1{ amin, amax };
	BoxCollider box2{ bmin, bmax };

	return (box1.minX <= box2.maxX &&
		box1.maxX >= box2.minX &&
		box1.minY <= box2.maxY &&
		box1.maxY >= box2.minY &&
		box1.minZ <= box2.maxZ &&
		box1.maxZ >= box2.minZ);
}

