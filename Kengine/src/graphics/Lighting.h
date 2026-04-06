#pragma once
#include "DirectXMath.h"

#define MAX_POINT_LIGHTS 32

struct PointLight
{
	DirectX::XMVECTOR position{ 0.0f, 0.0f, 0.0f };
	DirectX::XMVECTOR colour{ 1.0f, 1.0f, 1.0f };
	float strength = 10;
	bool enabled = true;

	float padding[2];
};

struct DirectionalLight
{
	DirectX::XMVECTOR directionFrom{ 0.0f, 0.0f, 0.0f };
	DirectX::XMVECTOR colour{ 1.0f, 1.0f, 1.0f };
};

struct SpotLight
{
	DirectX::XMVECTOR directionFrom{ 0.0f, 0.0f, 0.0f };
	DirectX::XMVECTOR colour{ 1.0f, 1.0f, 1.0f };
	float stength = 10;
	bool enabled = true;
	float coneWidth = 5;

	float padding;
};