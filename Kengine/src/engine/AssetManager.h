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

	DXTexture& GetTexture(std::string ID) { return TextureMap.at(ID); }

	DXMesh& GetMesh(std::string ID) { return MeshMap.at(ID); }

private:

	DXRenderer& dxRend;

	std::map<std::shared_ptr<DXTexture>, std::string> TextureMap;
	std::map<std::shared_ptr<DXMesh>, std::string> MeshMap;

	std::string obj = "obj", png = "png", jpg = "jpg", jpeg = "jpeg", bmp = "bmp";

	enum class FileExtension
	{
		UNKNOWN, OBJ, PNG, JPG, JPEG, BMP, NONE
	};

	FileExtension fileExe;


};

