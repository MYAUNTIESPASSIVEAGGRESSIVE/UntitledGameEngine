#pragma once
#include <string>
#include <memory>
#include <map>
#include "graphics/Debugger.h"
#include "graphics/DXTexture.h"
#include "graphics/DXMesh.h"

class DXRenderer;

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
			LOG("Mesh Map does not contain " + ID);
			return TextureMap.at(0);
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
			return MeshMap.at(0);
		}
		else return MeshMap.at(ID);
	}

private:

	DXRenderer& dxRend;

	// maps for assets
	std::map<std::string, DXTexture> TextureMap;
	std::map<std::string, DXMesh> MeshMap;

	enum class AssetType
	{
		UNKNOWN, TEXTURE, TEXTRANS, MESH, MESH2SIDE, NONE
	};

	AssetType aType = AssetType::UNKNOWN;

	AssetType CheckType(std::string type,
		bool isTransparent = false, bool isDoubleSided = false);

};

