#pragma once
#include <string>

struct ID3D11Device;
struct ID3D11DeviceContext;

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

struct ID3D11Buffer;

class DXRenderer;
class DXTexture;

class DXMaterial
{
public:
	DXMaterial(std::string name, DXRenderer& renderer,
		std::string vShaderFilename, std::string pShaderFilename,
		DXTexture* texture);

	DXTexture* GetTexture() { return texture; }

	virtual void Bind(); // set rendering state + bind then draw material

	~DXMaterial();

protected:

	struct CBufferBase // base mat type
	{

	};

	std::string name;

	DXRenderer& renderer;

	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* devcon = nullptr;
	ID3D11VertexShader* vShader = nullptr;
	ID3D11PixelShader* pShader = nullptr;
	ID3D11InputLayout* vLayout = nullptr;

	DXTexture* texture = nullptr;

	ID3D11Buffer* cbuffer = nullptr;

	void CreateCBuffer(unsigned int byteWidth, ID3D11Buffer*& targetBuffer);
	void UpdateCBuffer(CBufferBase& cbData, ID3D11Buffer*& targetBuffer);

};




