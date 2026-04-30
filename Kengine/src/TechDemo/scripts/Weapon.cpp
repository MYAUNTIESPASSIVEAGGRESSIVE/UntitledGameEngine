#include "Weapon.h"

Weapon::Weapon(std::string name, DXMesh* mesh, DXMaterial* material, ColliderType type)
	: GameObject(name, mesh, material, type, false)
{

}

void Weapon::Reload()
{
	//if()
}

void Weapon::Shoot()
{

}
