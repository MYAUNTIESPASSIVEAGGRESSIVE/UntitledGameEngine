#pragma once
#include "Transform.h"
#include "DirectXMath.h"

class Viewport
{
public:

	Transform transform;

	float fov = 65;
	float nearClippingPlane = 0.1f;
	float farClippingPlane = 1000.0f;

	DirectX::XMMATRIX GetViewMatrix();
	DirectX::XMMATRIX GetProjectionMatrix(int screenWidth, int screenHeight);

};

