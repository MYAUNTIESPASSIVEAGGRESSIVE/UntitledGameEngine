#include "Level.h"
#include "graphics/DXRenderer.h"
#include "engine/memory/AssetManager.h"
#include "engine/gameobjects/GameObject.h"
#include "graphics/materials/DXMaterial_Lit.h"

Level::Level(DXRenderer& dxRend, AssetManager& AM)
	: _dxRend(dxRend), _AM(AM) { }

void Level::InitLevel()
{
	_AM.LoadAsset("Assets/cube.obj", "SampleMesh");
	_AM.LoadAsset("Assets/SampleTexture.jpg", "SampleTexture");

	DXMaterial material{ "Test", _dxRend, "src/Compiled Shaders/BaseVertexShader.cso","src/Compiled Shaders/BasePixelShader.cso", &_AM.GetTexture("SampleTexture")};

	GameObject go_test{ "GO" , &_AM.GetMesh("SampleMesh"), &material, ColliderType::BOX, true };

	_dxRend.renderQueue.AddObject(&go_test);
}