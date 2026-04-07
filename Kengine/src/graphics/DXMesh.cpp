#include "DXMesh.h"
#include <d3d11.h>

#include "DXRenderer.h"
#include "ModelLoaders/OBJModelLoader.h"
#include "Debugger.h"

DXMesh::DXMesh(DXRenderer& renderer, std::string objPath, bool doubleSided)
	: dev(renderer.GetDevice()), devcon(renderer.GetDeviceContext()), isDoubleSided(doubleSided)
{
	OBJModelLoader ml{ objPath };

	D3D11_BUFFER_DESC bd = { 0 };
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = (unsigned int)ml.GetVertexBufferSize();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; 
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	if (FAILED(dev->CreateBuffer(&bd, NULL, &vBuffer)))
	{
		LOG("failed to create vertex buffer");
		return;
	}

	//copy the verticies into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(vBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); 
	memcpy(ms.pData, ml.GetVertexData(), ml.GetVertexBufferSize());
	devcon->Unmap(vBuffer, NULL);

	// fill in a buffer description
	D3D11_BUFFER_DESC indexBD = { 0 };
	indexBD.Usage = D3D11_USAGE_DEFAULT;
	indexBD.ByteWidth = ml.GetIndexBufferSize();
	indexBD.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// define the rosource data.
	D3D11_SUBRESOURCE_DATA initData = { 0 };
	initData.pSysMem = ml.GetIndexData();

	indexCount = (int)ml.GetIndexCount();

	if (FAILED(dev->CreateBuffer(&indexBD, &initData, &iBuffer)))
	{
		LOG("failed to create index buffer");
		return;
	}
}

void DXMesh::Render()
{
	// select which primitive we are using
	devcon->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// select which vertex buffer to use
	UINT stride = sizeof(VertexPosUVNorm);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset); 
	devcon->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);

	devcon->DrawIndexed(indexCount, 0, 0);
}
