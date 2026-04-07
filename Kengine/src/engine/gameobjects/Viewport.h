#pragma once
#include "Transform.h"
#include "DirectXMath.h"

class Viewport
{
public:

	Kengine::Transform transform;

	float fov = 65;
	float nearCliipingPlane = 0.1f;
	float farClippingPlane = 1000.0f;

	DirectX::XMMATRIX GetViewMatrix();
	DirectX::XMMATRIX GetProjectionMatrix(int screenWidth, int screenHeight);

};

