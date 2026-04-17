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

	enum class TextureType
	{
		Texture2D,
		Cubemap
	};

	DXTexture(DXRenderer& dxRend, std::string assetPath, std::string name, 
		bool transparent = false, TextureType type = TextureType::Texture2D);

	~DXTexture();

	//TODO: transparency and clipping textures

	ID3D11ShaderResourceView* GetTexture() { return texture; }
	ID3D11SamplerState* GetSampler() { return sampler; }

	bool isTransparent = false;


private:

	std::string texName;

	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;

	std::string path;

	ID3D11SamplerState* sampler = nullptr;
	ID3D11ShaderResourceView* texture = nullptr;

};