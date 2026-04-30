#include "Transform.h"

	DirectX::XMMATRIX Transform::GetWorldMatrix()
	{
		DirectX::XMMATRIX scaleMat = DirectX::XMMatrixScalingFromVector(scale);
		DirectX::XMMATRIX rotationMat = DirectX::XMMatrixRotationRollPitchYawFromVector(rotation);
		DirectX::XMMATRIX translationMat = DirectX::XMMatrixTranslationFromVector(position);

		return scaleMat * rotationMat * translationMat;
	}

	void Transform::Translate(DirectX::XMVECTOR translation)
	{
		position = DirectX::XMVectorAdd(position, translation);
	}

	void Transform::Rotate(DirectX::XMVECTOR inRotation)
	{
		rotation = DirectX::XMVectorAddAngles(rotation, inRotation);
	}

	DirectX::XMVECTOR Transform::GetForward()
	{
		float pitch = DirectX::XMVectorGetX(rotation);
		float yaw = DirectX::XMVectorGetY(rotation);

		DirectX::XMVECTOR direction
		{
			cosf(pitch) * sinf(yaw),
			sinf(pitch),
			cosf(pitch) * cosf(yaw),
		};
		
		return DirectX::XMVector3Normalize(direction);
	}

	DirectX::XMVECTOR Transform::GetUnitForward()
	{
		float pitch = DirectX::XMVectorGetX(rotation);
		float yaw = DirectX::XMVectorGetY(rotation);

		DirectX::XMVECTOR direction
		{
			cosf(pitch) * sinf(yaw),
			0.0,
			cosf(pitch) * cosf(yaw),
		};

		return DirectX::XMVector3Normalize(direction);
	}

	DirectX::XMVECTOR Transform::GetRight()
	{
		float pitch = DirectX::XMVectorGetX(rotation);
		float yaw = DirectX::XMVectorGetY(rotation);
		float roll = DirectX::XMVectorGetZ(rotation);

		DirectX::XMVECTOR direction
		{
			cosf(roll) * cosf(yaw) + sinf(roll) * sinf(pitch) * sinf(yaw),  // X
			sinf(roll) * cosf(pitch),									    // Y
			cosf(roll) * -sinf(yaw) + sinf(roll) * sinf(pitch) * cosf(yaw), // Z
		};

		return DirectX::XMVector3Normalize(direction);
	}

	// get the up vector
	DirectX::XMVECTOR Transform::GetUp()
	{
		DirectX::XMVECTOR cross = DirectX::XMVector3Cross(GetForward(), GetRight());

		return DirectX::XMVector3Normalize(cross);
	}

