#pragma once
#include <memory>
#include <string>
#include "Object.h"
#include "graphics/Lighting.h"

class PointLightObject
	: public Object
{
public:

	PointLightObject(std::string name, DirectX::XMVECTORF32 colour, float strength);

	PointLight pointLight;
};

