#pragma once
#include <string>

class DXRenderer;

struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;
struct ID3D11Device;
struct ID3D11DeviceContext;

class DXTexture
{

public:

	DXTexture(DXRenderer& dxRend, std::string assetPath);

	~DXTexture();

	//TODO: transparency and clipping textures

	ID3D11ShaderResourceView* GetTexture() { return texture; }
	ID3D11SamplerState* GetSampler() { return sampler; }

private:

	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;

	std::string path;

	ID3D11SamplerState* sampler = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

};

