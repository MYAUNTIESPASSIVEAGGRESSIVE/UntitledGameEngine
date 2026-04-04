#pragma once
#include "MathHelper.h"

namespace Kengine
{
	class Collision
	{
	public:

		static bool CircleCollision(Vector3 c1, float r1, Vector3 c2, float r2);

		static bool BoxCollision();
	};
}


