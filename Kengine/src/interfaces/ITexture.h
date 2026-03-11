#pragma once
#include <string>

class ITexture
{
public:
	virtual void LoadTexture(std::string assetPath) = 0;
};
