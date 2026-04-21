#pragma once
#include "Object.h"
#include "graphics/Lighting.h"

class DirectionalLightObject :
    public Object
{
public:

    DirectionalLightObject(std::string name, DirectX::XMVECTOR directionFrom, DirectX::XMVECTOR colour);

    DirectionalLight directionalLight;

};

