#include "DirectionalLightObject.h"

DirectionalLightObject::DirectionalLightObject(std::string name, DirectX::XMVECTOR directionFrom,
	DirectX::XMVECTOR colour) : Object(name, name)
{
	directionalLight = { directionFrom, colour };
}
