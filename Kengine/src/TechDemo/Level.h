#pragma once
#include <vector>

class AssetManager;
class DXRenderer;

class DXMesh;
class DXTexture;

class GameObject;

class Level
{
public:

	Level(DXRenderer& dxRend, AssetManager& AM);

	void InitLevel();

	//std::vector<GameObject*> gameObjectsInLevel;

private:

	DXRenderer& _dxRend;

	AssetManager& _AM;
};

