#pragma once
#include <memory>
#include <string>
#include <map>
#include "graphics/Debugger.h"

class DXRenderer;

class DXMesh;

class DXTexture;

class AssetManager
{

public:

	AssetManager(DXRenderer& inRend);

	void LoadAsset(std::string filePath, std::string ID,
		bool isTransparent = false, bool isDoubleSided = false);

	std::shared_ptr<DXTexture> GetTexture(std::string ID)
	{
		auto asset = TextureMap[ID].lock();

		if (!asset) LOG("Texture is not in map or innaccessible");

		return asset;
	}

	std::shared_ptr<DXMesh> GetMesh(std::string ID)
	{
		auto asset = MeshMap[ID].lock();

		if (!asset) LOG("Texture is not in map or innaccessible");

		return asset;
	}

private:

	DXRenderer& dxRend;

	std::map<std::string, std::weak_ptr<DXTexture>> TextureMap;
	std::map<std::string, std::weak_ptr<DXMesh>> MeshMap;

	std::string obj = "obj", png = "png", jpg = "jpg", jpeg = "jpeg", bmp = "bmp";

	enum class AssetType
	{
		UNKNOWN, TEXTURE, TEXTRANS, MESH, MESH2SIDE, NONE
	};

	AssetType aType;

	AssetType CheckType(std::string type,
		bool isTransparent = false, bool isDoubleSided = false);



};

