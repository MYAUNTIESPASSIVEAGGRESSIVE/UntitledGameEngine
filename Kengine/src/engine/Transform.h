#pragma once
#include "MathHelper.h"
namespace Kengine
{
	class Transform
	{
	public:

		Vector3 position{ 0.0f, 0.0f, 0.0f };
		Vector3 rotation{ 0.0f, 0.0f, 0.0f };
		Vector3 scale{ 1.0f, 1.0f, 1.0f };

		void Translate(Vector3 translation);
		void Rotate(Vector3 inRotation);

		Vector3 GetForward();
		Vector3 GetRight();
		Vector3 GetUp();
	};
}


