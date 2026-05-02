#include "PointLightObject.h"

PointLightObject::PointLightObject(std::string name, DirectX::XMVECTORF32 colour, float strength)
	: Object(name, name)
{
	pointLight = { transform.position, colour, strength, true };
}

