#include "DXTexture.h"
#include "WICTextureLoader.h" // REGULAR TEXTURES
#include "DDSTextureLoader.h" // CUBE MAPS
#include "d3d11.h"
#include "DXRenderer.h"
#include "Debugger.h"

DXTexture::DXTexture(DXRenderer& dxRend, std::string assetPath, bool transparent)
	:dev(dxRend.GetDevice()), devcon(dxRend.GetDeviceContext()), isTransparent(transparent)
{
	std::wstring assetloc = std::wstring(assetPath.begin(), assetPath.end());

	// create WICtexture
	DirectX::CreateWICTextureFromFile(dev, devcon, assetloc.c_str(), NULL, &texture);

	// set filters
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(D3D11_SAMPLER_DESC));
	/* IF RENDER SETTINGS = LINEAR -> sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR*/
	/* IF RENDER SETTINGS = POINT -> sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT*/
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	sampDesc.MaxAnisotropy = 8;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if (FAILED(dev->CreateSamplerState(&sampDesc, &sampler)))
	{
		LOG("Failed to create sampler state");
	}
}

DXTexture::~DXTexture()
{
	if (texture) texture = nullptr;
	if (sampler) sampler = nullptr;
}
