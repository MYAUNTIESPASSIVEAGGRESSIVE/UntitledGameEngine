#pragma once

class AssetManager;
class DXRenderer;

class DXMesh;
class DXTexture;

class Level
{
public:

	Level(DXRenderer& dxRend, AssetManager& AM);

	void InitLevel();

private:

	DXRenderer& _dxRend;

	AssetManager& _AM;
};

