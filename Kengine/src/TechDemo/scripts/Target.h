#pragma once
#include "engine/gameobjects/GameObject.h"

class Target :
    public GameObject
{
public:

    float health;

    void TakeDamage(float dmg)
    {
        health = -dmg;
    }

    virtual void Update();

    void DestorySelf();

};

