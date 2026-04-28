#pragma once
#include "engine/gameobjects/GameObject.h"
#include "engine/gameobjects/Viewport.h"

class Viewport;

class Player :
    public GameObject
{
public:

    Player(std::string name, ColliderType type, Viewport cam);

    Viewport playercam;

    float moveSpeed = 10;

    virtual void Update();

    void HandleInput();
};

