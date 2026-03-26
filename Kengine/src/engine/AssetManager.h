#pragma once
#include <memory>
#include <string>
#include <map>

class DXRenderer;

class DXMesh;

class DXTexture;

class AssetManager
{

public:

	AssetManager(DXRenderer& inRend);

	void Load(std::string filePath, std::string ID);

private:

	DXRenderer& dxRend;

	std::map<std::shared_ptr<DXTexture>, std::string> TextureMap;
	std::map<std::shared_ptr<DXMesh>, std::string> MeshMap;

};

