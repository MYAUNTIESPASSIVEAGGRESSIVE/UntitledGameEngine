#pragma once
#include <string>

class DXRenderer;

struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

class DXTexture
{

public:

	DXTexture(DXRenderer& dxRend, std::string assetPath);
	~DXTexture();

	//TODO: transparency and clipping textures

private:

	ID3D11SamplerState* sampler = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

};

