#include "Transform.h"
namespace Kengine
{
	void Transform::Translate(Vector3 translation)
	{
		position = operator+(position, translation);
	}

	void Transform::Rotate(Vector3 inRotation)
	{

	}

	Vector3 Transform::GetForward()
	{
		return Vector3();
	}

	Vector3 Transform::GetRight()
	{
		return Vector3();
	}

	Vector3 Transform::GetUp()
	{
		return Vector3();
	}
}


