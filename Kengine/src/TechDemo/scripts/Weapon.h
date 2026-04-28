#pragma once
#include "engine/gameobjects/GameObject.h"

class Weapon :
    public GameObject
{
public:

    //Weapon(std::string name, DXMesh* mesh, DXMaterial* material, ColliderType type);

    float Damage = 3;

    int CurrentAmmo = 5;

    int MagSize = 5;

    int ReserveAmmo = 30;

    void Reload();

    void Shoot();

};

