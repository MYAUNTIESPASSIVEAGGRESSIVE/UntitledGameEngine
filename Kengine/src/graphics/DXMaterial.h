#pragma once

struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

class DXMaterial
{
protected:

	DXMaterial(ID3D11SamplerState* sampler);

	~DXMaterial();

	virtual void Render();

private:


};

