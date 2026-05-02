#pragma once
#include "engine/gameobjects/Viewport.h"
#include "engine/RenderQueue.h"

#define MAX_POINT_LIGHTS 32

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

struct ID3D11DepthStencilView;

struct ID3D11RasterizerState;

struct ID3D11BlendState;

struct ID3D11DepthStencilState;

struct ID3D11Buffer;

class DXWindow;

class GameObject;

class DXRenderer
{
public:

	Viewport camera;

	DXRenderer(DXWindow& inWindow);
	void Release();
	void RenderFrame();
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return devcon; }
	
	GameObject* SkyBox = nullptr;

private:


	DXWindow& window;

	// device and devcon
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* devcon = nullptr;

	// swapchain and backbuffer
	IDXGISwapChain* swapchain = nullptr;
	ID3D11RenderTargetView* backBuffer = nullptr;

	// depth, rasteriser states and blend states
	ID3D11DepthStencilView* depthBuffer = NULL;
	ID3D11DepthStencilState* depthWriteOff = nullptr;

	ID3D11RasterizerState* rasterizerCullBack = nullptr;
	ID3D11RasterizerState* rasterizerCullFront = nullptr;
	ID3D11RasterizerState* rasterizerCullNone = nullptr;

	ID3D11BlendState* blendOpaque = nullptr;
	ID3D11BlendState* blendTransparent = nullptr;

	// const buffers
	ID3D11Buffer* cBuffer_PerObject = nullptr;
	ID3D11Buffer* cBuffer_PerFrame = nullptr;

	long InitD3D();
	void InitGraphics();
	long InitDepthBuffer();
	void DrawSkyBox();
};

