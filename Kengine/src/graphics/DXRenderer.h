#pragma once
#include <vector>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

struct ID3D11DepthStencilView;

struct ID3D11RasterizerState;

struct ID3D11BlendState;

struct ID3D11DepthStencilState;

class DXWindow;

class DXRenderer
{
public:

	DXRenderer(DXWindow& inWindow);
	void Release();
	void RenderFrame();
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return devcon; }

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

	long InitD3D();
	void InitGraphics();
	long InitDepthBuffer();
};

