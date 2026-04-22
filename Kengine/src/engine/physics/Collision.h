#pragma once
#include <DirectXMath.h>

static class Collision
{
public:

	static bool OnCircleCollide(DirectX::XMVECTOR c1, DirectX::XMVECTOR c2, float c1r, float c2r);

	static bool OnBoxCollide(DirectX::XMVECTOR c1, DirectX::XMVECTOR c2);
};


