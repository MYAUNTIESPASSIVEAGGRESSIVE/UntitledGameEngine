#include "AssetManager.h"
#include "graphics/Debugger.h"
#include "graphics/DXRenderer.h"
#include "graphics/DXMesh.h"
#include "graphics/DXTexture.h"

AssetManager::AssetManager(DXRenderer& inRend)
	:dxRend(inRend)
{ }


void AssetManager::LoadAsset(std::string filePath, std::string ID,
	bool isTransparent, bool isDoubleSided)
{
	aType = AssetType::UNKNOWN;
	// extract final .fileext
	// if/switch texture then contruct texture or if/switch obj then constuct mesh
	std::string subs;
	auto npos = filePath.find('.');
	if (npos != std::string::npos)
		subs = filePath.substr(npos + 1);

	if (!subs.empty() && aType == AssetType::UNKNOWN)
		CheckType(subs);

	switch (aType)
	{
	case(AssetType::MESH):
	{
		MeshMap.emplace(ID, DXMesh(dxRend, filePath, ID));
		LOG("Mesh added to map");

		aType = AssetType::UNKNOWN;
		break;
	}
	case(AssetType::MESH2SIDE):
	{
		MeshMap.emplace(ID, DXMesh(dxRend, filePath, ID, true));
		LOG("Mesh added to map");

		aType = AssetType::UNKNOWN;
		break;
	}
	case(AssetType::TEXTURE):
	{
		TextureMap.emplace(ID, DXTexture(dxRend, filePath, ID));
		LOG("Texture added to map");

		aType = AssetType::UNKNOWN;
		break;
	}
	case(AssetType::TEXTRANS):
	{
		TextureMap.emplace(ID, DXTexture(dxRend, filePath, ID, true));
		LOG("Texture added to map");

		aType = AssetType::UNKNOWN;
		break;
	}

	}
}

AssetManager::AssetType AssetManager::CheckType(std::string type,
	bool isTransparent, bool isDoubleSided)
{
	if (type == obj)
		return aType = isDoubleSided ? AssetType::MESH2SIDE : AssetType::MESH;

	if (type == png || type == jpg || type == jpeg || type == bmp)
		return aType = isTransparent ? AssetType::TEXTRANS : AssetType::TEXTURE;

	else return AssetType::NONE;
}

