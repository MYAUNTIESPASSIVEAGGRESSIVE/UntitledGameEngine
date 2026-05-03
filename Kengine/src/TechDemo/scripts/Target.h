#pragma once
#include "engine/gameobjects/GameObject.h"

class Target :
    public GameObject
{
public:

    Target(std::string name = "", std::string tag = "Target", DXMesh* mesh = nullptr, DXMaterial* material = nullptr, ColliderType type = ColliderType::SPHERE, bool SimulatePhysics = true, float rad = 0.5f);

    float health;

    void TakeDamage(float dmg)
    {
        health = -dmg;
    }

    virtual void Update();

};

