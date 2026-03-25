#pragma once
#include <string>

class IMesh
{
public:
	virtual void LoadMesh(std::string assetPath) = 0;
};