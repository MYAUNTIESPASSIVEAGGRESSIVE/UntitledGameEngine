#include "DXMaterial_Transparent.h"
#include "d3d11.h"
#include "engine/gameobjects/GameObject.h"
#include "graphics/DXTexture.h"
#include "graphics/DXRenderer.h"

DXMaterial_Transparent::DXMaterial_Transparent(std::string name, DXRenderer& renderer, std::string vShaderFilename, std::string pShaderFilename, DXTexture* texture)
	: DXMaterial_Lit(name, renderer, vShaderFilename, pShaderFilename, texture)
{
	CreateCBuffer(sizeof(CBufferLighting), cbuffer);
	CreateCBuffer(sizeof(CBufferPS), cbufferPixelShader);
}

void DXMaterial_Transparent::Bind()
{
	DXMaterial::Bind();

	if (cbufferPixelShader != nullptr)
	{
		devcon->PSSetConstantBuffers(0, 1, &cbufferPixelShader);
	}

	if (skyboxTexture != nullptr)
	{
		ID3D11ShaderResourceView* t = skyboxTexture->GetTexture();
		devcon->PSGetShaderResources(1, 1, &t);
	}
}

void DXMaterial_Transparent::UpdateMaterial(GameObject* GO)
{
	using namespace DirectX;
	DXMaterial_Lit::UpdateMaterial(GO);

	CBufferPS cbpsData;
	cbpsData.transparency = transparency;
	UpdateCBuffer(cbpsData, cbufferPixelShader);
}


