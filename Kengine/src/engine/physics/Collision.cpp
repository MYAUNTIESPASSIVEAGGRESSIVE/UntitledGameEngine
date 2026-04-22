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
bool Collision::OnBoxCollide(DirectX::XMVECTOR v1, DirectX::XMVECTOR v2)
{




	return false;
}

