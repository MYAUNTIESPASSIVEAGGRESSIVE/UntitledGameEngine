#include "DXTexture.h"
#include "WICTextureLoader.h" // REGULAR TEXTURES
#include "DDSTextureLoader.h" // CUBE MAPS
#include "d3d11.h"

#include "DXRenderer.h"



DXTexture::DXTexture(DXRenderer& dxRend, std::string assetPath)
{
	ID3D11Device* dev = dxRend.GetDevice();
	ID3D11DeviceContext* devcon = dxRend.GetDeviceContext();
	// get wide string of assets path
	std::wstring path = std::wstring(assetPath.begin(), assetPath.end());

	// create WICtexture
	DirectX::CreateWICTextureFromFile(dev, devcon, path.c_str(), NULL, &texture);

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
	//anisotropicDesc.BorderColor = 0.0f;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = 0;
}

DXTexture::~DXTexture()
{
	if (texture) texture = nullptr;

	if (sampler) sampler = nullptr;
}
