#include "IRenderer.h"
#include "DXRenderer.h"

IRenderer::IRenderer(DXRenderer* _dxRend)
	:dxRend(_dxRend)
{
}

bool IRenderer::InitDrawCall()
{
	return false;
}

void IRenderer::IRenderFrame()
{
	dxRend->RenderFrame();
}
