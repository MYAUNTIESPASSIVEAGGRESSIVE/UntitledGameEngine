#pragma once
#include <string>
#include <memory>

struct ID3D11Device;
struct ID3D11DeviceContext;

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

struct ID3D11Buffer;

class DXRenderer;
class DXTexture;

class GameObject;

class DXMaterial
{
public:
	DXMaterial(std::string name, DXRenderer& renderer,
		std::string vShaderFilename, std::string pShaderFilename,
		 DXTexture* texture);

	//DXMaterial(const DXMaterial&) = delete;
	//DXMaterial& operator=(const DXMaterial&) = delete;
	
	DXTexture* GetTexture() { return texture; }

	std::string GetName() { return name; }

	virtual void Bind(); // set rendering state + bind then draw material

	virtual void UpdateMaterial(GameObject* entiry) {}

	~DXMaterial();

	int GetRenderOrder() { return renderOrder; }
	void SetRenderOrder(int order) { renderOrder = order; }

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

	int renderOrder = 1000;

};




