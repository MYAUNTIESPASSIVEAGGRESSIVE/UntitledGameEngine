#include "PointLightObject.h"

PointLightObject::PointLightObject(std::string name, DirectX::XMVECTOR colour, float strength)
	: Object(name)
{
	pointLight = { transform.position, colour, strength, true };
}

