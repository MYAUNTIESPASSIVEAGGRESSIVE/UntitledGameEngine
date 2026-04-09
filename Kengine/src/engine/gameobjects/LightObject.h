#pragma once
#include <memory>
#include <string>
#include "Transform.h"
#include "graphics/Lighting.h"

class LightObject
{
public:

	enum class LightType
	{
		POINT,
		DIRECTIONAL,
		SPOT
	};

	Transform transform;

	std::string GetName() { return objectName; };

	LightObject(std::string name, LightType type);


private:

	std::string objectName = "LightObject";


};

