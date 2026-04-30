#pragma once
#include "engine/gameobjects/GameObject.h"

class Weapon;

class Player :
    public GameObject
{
public:

    Player(std::string name, ColliderType type, float circlerad = 1);

    float moveSpeed = 10;

    virtual void Update();

    Weapon* Gun = nullptr;
};

