#pragma once
#include "engine/gameobjects/GameObject.h"

class Player :
    public GameObject
{
public:
    float moveSpeed;

    virtual void Update() override;
};

