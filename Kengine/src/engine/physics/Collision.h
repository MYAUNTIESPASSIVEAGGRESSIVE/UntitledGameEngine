#pragma once
#include <DirectXMath.h>

struct BoxCollider
{
	DirectX::XMVECTOR min;
	DirectX::XMVECTOR max;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	BoxCollider(DirectX::XMVECTOR amin, DirectX::XMVECTOR amax)
		:min(amin), max(amax)
	{
		minX = DirectX::XMVectorGetX(min);
		maxX = DirectX::XMVectorGetX(max);

		minY = DirectX::XMVectorGetY(min);
		maxY = DirectX::XMVectorGetY(max);

		minZ = DirectX::XMVectorGetZ(min);
		maxZ = DirectX::XMVectorGetZ(max);
	};
};


static class Collision
{
public:

	static bool OnCircleCollide(DirectX::XMVECTOR c1, DirectX::XMVECTOR c2, float c1r, float c2r);

	static bool OnBoxCollide(DirectX::XMVECTOR amin, DirectX::XMVECTOR amax, DirectX::XMVECTOR bmin, DirectX::XMVECTOR bmax);
};


