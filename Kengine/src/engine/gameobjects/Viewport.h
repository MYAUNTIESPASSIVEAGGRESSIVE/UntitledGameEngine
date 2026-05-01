#pragma once
#include "DirectXMath.h"
#include "Transform.h"
#include "engine/physics/Collision.h"

class GameObject;

class Viewport
{
public:

	Transform transform;

	float fov = 65;
	float nearClippingPlane = 0.1f;
	float farClippingPlane = 1000.0f;

	DirectX::XMMATRIX GetViewMatrix();
	DirectX::XMMATRIX GetProjectionMatrix(int screenWidth, int screenHeight);

	void SetParentObject(GameObject* object);
	GameObject* GetParentObject() { return parentObject; }

	Raycast ray;

private:

	GameObject* parentObject = nullptr;

};

