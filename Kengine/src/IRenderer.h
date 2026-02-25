#pragma once
class DXRenderer;

class IRenderer
{
protected:

	DXRenderer* dxRend;

public:
	IRenderer(DXRenderer *_dxRend);
	~IRenderer() { delete dxRend; }

	bool InitDrawCall();
	void IRenderFrame();
};

