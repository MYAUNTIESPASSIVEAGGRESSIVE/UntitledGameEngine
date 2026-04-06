#include "Collision.h"
namespace Kengine
{
	bool Collision::OnCircleCollide(Vector3 c1, Vector3 c2)
	{
		float distance = Distance(c1, c2);

		float c1r = c1.Magnitude();
		float c2r = c2.Magnitude();

		return distance <= c1r + c2r ? true : false;
	}

	bool Collision::OnBoxCollide(Vector3 v1, Vector3 v2)
	{



		return false;
	}


}

