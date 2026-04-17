#pragma once
#include <string>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;

class DXRenderer;

class DXMesh
{
private:

	std::string meshName;

	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;
	ID3D11Buffer* vBuffer = NULL;
	ID3D11Buffer* iBuffer = NULL;

	unsigned int indexCount = 0;

public:

	DXMesh(DXRenderer& renderer, std::string objPath, std::string name, bool doubleSided = false);
	void Render();

	bool isDoubleSided = false;
};

