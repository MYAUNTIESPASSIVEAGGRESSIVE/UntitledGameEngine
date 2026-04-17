#pragma once
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

	// gets reference texture
	DXTexture& GetTexture(std::string ID)
	{
		auto it = TextureMap.find(ID);

		if (it == TextureMap.end())
		{
			LOG("Texture Map does not contain " + ID);
			return;
		}
		else return TextureMap.at(ID);
	}

	// gets reference to mesh
	DXMesh& GetMesh(std::string ID)
	{
		auto it = MeshMap.find(ID);

		if (it == MeshMap.end())
		{
			LOG("Mesh Map does not contain " + ID);
			return;
		}
		else return MeshMap.at(ID);
	}

private:

	DXRenderer& dxRend;

	// maps for assets
	std::map<std::string, DXTexture> TextureMap;
	std::map<std::string, DXMesh> MeshMap;

	// string which defines the asset types you need
	std::string obj = "obj", png = "png", jpg = "jpg", jpeg = "jpeg", bmp = "bmp";

	enum class AssetType
	{
		UNKNOWN, TEXTURE, TEXTRANS, MESH, MESH2SIDE, NONE
	};

	AssetType aType;

	AssetType CheckType(std::string type,
		bool isTransparent = false, bool isDoubleSided = false);

};

