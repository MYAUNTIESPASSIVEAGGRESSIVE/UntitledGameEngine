#pragma once
#include "engine/gameobjects/GameObject.h"

enum CurrentDirection
{
    Forward,
    Right,
    Left,
    Backward
};

class Weapon;

class Player :
    public GameObject
{
public:

    Player(std::string name, std::string tag, ColliderType type, float circlerad = 1);

    float moveSpeed = 10;

    virtual void Update();

    Weapon* Gun = nullptr;

    CurrentDirection direction;

    bool blockedforward = false, blockedleft = false, blockedright = false, blockedbackward = false;
};

