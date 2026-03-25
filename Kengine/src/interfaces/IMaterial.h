#pragma once
#include <string>

class IMaterial
{
public:

	virtual void LoadMaterial(std::string assetPath) = 0;
};