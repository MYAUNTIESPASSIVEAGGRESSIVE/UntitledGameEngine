#include "Viewport.h"
#include "GameObject.h"

DirectX::XMMATRIX Viewport::GetViewMatrix()
{
	DirectX::XMVECTOR eyePos = transform.position;
	DirectX::XMVECTOR lookAt = transform.GetForward();
	DirectX::XMVECTOR camUp = transform.GetUp();


	return DirectX::XMMatrixLookToLH(eyePos, lookAt, camUp); // looks foward (at the object)
}

DirectX::XMMATRIX Viewport::GetProjectionMatrix(int screenWidth, int screenHeight)
{
	return DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(fov),
		screenWidth / (float)screenHeight,
		nearClippingPlane,
		farClippingPlane);
}

void Viewport::SetParentObject(GameObject* object)
{
	transform.position = object->transform.position;

	parentObject = object;
}
