#pragma once
#include "DXMaterial.h"
#include "graphics/Lighting.h"

class DXMaterial_Lit :
    public DXMaterial
{
public:
    float reflectiveness = 0.1f;

    DXMaterial_Lit(std::string name, DXRenderer& renderer,
        std::string vShaderFilename, std::string pShaderFilename,
        DXTexture* texture);

    virtual void Bind() override;

    virtual void UpdateMaterial(GameObject* GO) override;

    void SetReflectionTexture(DXTexture* reflectionTexture) { skyboxTexture = reflectionTexture; }

protected:

    DXTexture* skyboxTexture = nullptr;
    ID3D11Buffer* cbufferPixelShader = nullptr;

    struct DirectionalLightCBData
    {
        DirectX::XMVECTOR transposedDirection;
        DirectX::XMVECTOR colour;
    };

    struct PointLightCBData
    {
        DirectX::XMVECTOR position;
        DirectX::XMVECTOR colour;
        float strength = 1;
        unsigned int enabled = 0;
        DirectX::XMFLOAT2 padding;
    };

    struct CBufferLighting : CBufferBase
    {
        DirectX::XMVECTOR ambientLightColour{ 1,1,1,1 };
        DirectionalLightCBData directionalLight;
        PointLightCBData pointLights[MAX_POINT_LIGHTS];
    };

    struct CBufferPS : CBufferBase
    {
        float reflectiveness;
        DirectX::XMFLOAT3 padding;
    };
};

