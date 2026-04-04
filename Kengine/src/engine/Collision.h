#pragma once
#include "MathHelper.h"

namespace Kengine
{
	class Collision
	{
	public:

		static bool OnCircleCollide(Vector3 c1, Vector3 c2);

		static bool OnBoxCollide(Vector3 c1, Vector3 c2);
	};
}


