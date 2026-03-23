#include "Transform.h"
namespace Kengine
{
	Matrix Transform::GetWorldMatrix()
	{
		Matrix scaleMat = ScaleFromVector(scale);
		Matrix rotationMat = RotationFromVector(rotation);
		Matrix translationMat = TranslateFromVector(position);

		return scaleMat * rotationMat * translationMat;
	}

	void Transform::Translate(Vector3 translation)
	{
		position = operator+(position, translation);
	}

	void Transform::Rotate(float inRotation)
	{
		RotateVector3(rotation, inRotation);
	}

	Vector3 Transform::GetForward()
	{
		float pitch = rotation.x;
		float yaw = rotation.y;

		Vector3 direction
		{
			cosf(pitch) * sinf(yaw),
			sinf(pitch),
			cosf(pitch) * cosf(yaw),
		};

		return direction.Normalized();
	}

	Vector3 Transform::GetRight()
	{
		float pitch = rotation.x;
		float yaw = rotation.y;
		float roll = rotation.z;

		Vector3 direction
		{
			cosf(roll) * cosf(yaw) + sinf(roll) * sinf(pitch) * sinf(yaw),  // X
			sinf(roll) * cosf(pitch),									    // Y
			cosf(roll) * -sinf(yaw) + sinf(roll) * sinf(pitch) * cosf(yaw), // Z
		};

		return direction.Normalized();
	}

	Vector3 Transform::GetUp()
	{
		Vector3 cross = CrossProduct(GetForward(), GetRight());

		return cross.Normalized();
	}
}


