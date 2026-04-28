#include "DXRenderer.h"
#include "Debugger.h"
#include "d3d11.h"
#include "DXWindow.h"
#include "DirectXColors.h"
#include "DirectXMath.h"
#include "engine/gameobjects/GameObject.h"
#include "materials/DXMaterial.h"
#include "DXMesh.h"
#include "DXTexture.h"
using namespace DirectX;

struct CBuffer_PerObject
{
	XMMATRIX World;
	XMMATRIX WVP;
};

struct CBuffer_PerFrame
{
	XMFLOAT3 camPos;
	float padding;
};

DXRenderer::DXRenderer(DXWindow& inWindow/*RenderQueue* renderQueue*/)
	: window(inWindow) //renderQueue(renderQueue)
{
	if (InitD3D() != S_OK)
	{
		LOG("Failed to initalise D3D renderer");
		return;
	}

	InitGraphics();
}


long DXRenderer::InitD3D()
{
	// swapchain desc
	DXGI_SWAP_CHAIN_DESC scd = {};

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = window.GetWidth();
	scd.BufferDesc.Height = window.GetHeight();
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = window.GetHandle();
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&device,
		NULL,
		&devcon);

	// get the address of the back buffer
	ID3D11Texture2D* backBufferTexture = nullptr;

	// get the back buffer from the swap chain
	hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(hr))
	{
		LOG("failed to create backbuffer texture.");
		return hr;
	}

	hr = device->CreateRenderTargetView(backBufferTexture, NULL, &backBuffer);

	backBufferTexture->Release();
	if (FAILED(hr))
	{
		LOG("failed to create backbuffer view.");
		return hr;
	}

	// init the depth buffer
	hr = InitDepthBuffer();
	if (FAILED(hr))
	{
		LOG("Failed to create depth buffer");
		return hr;
	}

	devcon->OMSetRenderTargets(1, &backBuffer, depthBuffer);

	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)window.GetWidth();
	viewport.Height = (float)window.GetHeight();
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	devcon->RSSetViewports(1, &viewport);

	if (FAILED(hr))
	{
		LOG("failed to create a renderer");
		return hr;
	}

	return S_OK;
}

void DXRenderer::InitGraphics()
{
	D3D11_BUFFER_DESC cbd = { 0 };
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(CBuffer_PerObject);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (FAILED(device->CreateBuffer(&cbd, NULL, &cBuffer_PerObject)))
	{
		LOG("failed to create Cbuffer_perobj");
	}

	cbd.ByteWidth = sizeof(CBuffer_PerFrame);

	if (FAILED(device->CreateBuffer(&cbd, NULL, &cBuffer_PerFrame)))
	{
		LOG("failed to create Cbuffer_perframe");
	}

	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
	rsDesc.CullMode = D3D11_CULL_NONE;
	rsDesc.FillMode = D3D11_FILL_SOLID;
	//rsDesc.FillMode = D3D11_FILL_WIREFRAME; // use for debugging

	// create no culling rasteriser
	device->CreateRasterizerState(&rsDesc, &rasterizerCullNone);

	// create backface culling rasteriser
	rsDesc.CullMode = D3D11_CULL_BACK;
	device->CreateRasterizerState(&rsDesc, &rasterizerCullBack);

	// create front rasteriser
	rsDesc.CullMode = D3D11_CULL_FRONT;
	device->CreateRasterizerState(&rsDesc, &rasterizerCullFront);

	D3D11_BLEND_DESC bdDesc = { 0 };
	bdDesc.IndependentBlendEnable = FALSE;
	bdDesc.AlphaToCoverageEnable = FALSE;
	bdDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bdDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bdDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bdDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bdDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bdDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bdDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// transparent blend state
	bdDesc.RenderTarget[0].BlendEnable = TRUE;
	device->CreateBlendState(&bdDesc, &blendTransparent);

	// opaque blend state
	bdDesc.RenderTarget[0].BlendEnable = TRUE;
	device->CreateBlendState(&bdDesc, &blendOpaque);


	D3D11_DEPTH_STENCIL_DESC dsDesc = { 0 };
	//depth test params
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	device->CreateDepthStencilState(&dsDesc, &depthWriteOff);
}

long DXRenderer::InitDepthBuffer()
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC scd = {};
	swapchain->GetDesc(&scd);

	D3D11_TEXTURE2D_DESC tex2dDesc = { 0 };
	tex2dDesc.Width = window.GetWidth();
	tex2dDesc.Height = window.GetHeight();
	tex2dDesc.ArraySize = 1;
	tex2dDesc.MipLevels = 1;
	tex2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2dDesc.SampleDesc.Count = scd.SampleDesc.Count;
	tex2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* zBufferTexture;
	hr = device->CreateTexture2D(&tex2dDesc, NULL, &zBufferTexture);
	if (FAILED(hr))
	{
		LOG("Failed to create Z-Buffer Texture");
		return E_FAIL;
	}

	// create the depth buffer view
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.Format = tex2dDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = device->CreateDepthStencilView(zBufferTexture, &dsvDesc, &depthBuffer);
	if (FAILED(hr))
	{
		LOG("Failed to create depth stencil view");
		return E_FAIL;
	}

	zBufferTexture->Release();

	return S_OK;
}


void DXRenderer::RenderFrame()
{
	// clear back buffer with colour
	devcon->ClearRenderTargetView(backBuffer, DirectX::Colors::Gray);
	devcon->ClearDepthStencilView(depthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	CBuffer_PerFrame cbufferPerFrameData;
	XMStoreFloat3(&cbufferPerFrameData.camPos, camera.transform.position);
	devcon->UpdateSubresource(cBuffer_PerFrame, NULL, NULL, &cbufferPerFrameData, NULL, NULL);
	devcon->VSSetConstantBuffers(11, 1, &cBuffer_PerFrame);

	CBuffer_PerObject cbufferData;
	XMMATRIX view = camera.GetViewMatrix();
	XMMATRIX projection = camera.GetProjectionMatrix(window.GetWidth(), window.GetHeight());

	for (auto& go : renderQueue.RenderableObjects)
	{
		XMMATRIX world = go->transform.GetWorldMatrix();
		cbufferData.World = world;
		cbufferData.WVP = world * view * projection;

		devcon->UpdateSubresource(cBuffer_PerObject, NULL, NULL, &cbufferData, NULL, NULL);
		devcon->VSSetConstantBuffers(12, 1, &cBuffer_PerObject);

		devcon->RSSetState(go->GetObjectMesh()->isDoubleSided ?
			rasterizerCullNone : rasterizerCullBack);

		devcon->OMSetBlendState(go->GetObjectMaterial()->GetTexture()->isTransparent ?
			blendTransparent : blendOpaque, 0, 0xffffffff);

		devcon->OMSetDepthStencilState(go->GetObjectMaterial()->GetTexture()->isTransparent ?
			depthWriteOff : nullptr, 1);


		go->GetObjectMaterial()->UpdateMaterial(go);
		go->GetObjectMaterial()->Bind();
		go->GetObjectMesh()->Render();
	}

	// flip the back and front buffers
	swapchain->Present(0, 0);
}

// cleanup
void DXRenderer::Release()
{
	if (backBuffer) backBuffer->Release();
	if (swapchain) swapchain->Release();
	if (device) device->Release();
	if (devcon) devcon->Release();
	if (depthBuffer) depthBuffer->Release();
}
