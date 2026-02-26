#pragma once
class DXRenderer;

class IRenderer
{
protected:

	DXRenderer* dxRend;

public:
	IRenderer(DXRenderer *_dxRend);
	~IRenderer() { delete dxRend; }

	virtual bool InitDrawCall() = 0;
	virtual void IRenderFrame() = 0;
};

