#pragma once
#include <DirectXMath.h>

namespace Kengine
{
	class Collision
	{
	public:

		static bool OnCircleCollide(DirectX::XMVECTOR c1, DirectX::XMVECTOR c2);

		static bool OnBoxCollide(DirectX::XMVECTOR c1, DirectX::XMVECTOR c2);
	};
}


