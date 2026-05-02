#pragma once
#include "DXMaterial_Lit.h"
#include "graphics/Lighting.h"

class DXMaterial_Transparent :
    public DXMaterial_Lit
{
public:
    float transparency = 0.1f;

    DXMaterial_Transparent(std::string name, DXRenderer& renderer,
        std::string vShaderFilename, std::string pShaderFilename,
        DXTexture* texture);

    virtual void Bind() override;

    virtual void UpdateMaterial(GameObject* GO) override;

    void SetReflectionTexture(DXTexture* reflectionTexture) { skyboxTexture = reflectionTexture; }

    int renderOrder = 3000;

protected:

    ID3D11Buffer* cbufferPixelShader = nullptr;

    struct CBufferPS : CBufferBase
    {
        float transparency;
        DirectX::XMFLOAT3 padding;
    };

};



