#include "Weapon.h"
#include "engine/RenderQueue.h"
#include "Target.h"

Weapon::Weapon(std::string name, DXMesh* mesh, DXMaterial* material, ColliderType type)
	: GameObject(name, name, mesh, material, type, false)
{
	gunray = { transform, {0,0,5}, 4 };
}

void Weapon::Reload()
{
	//if()
}

void Weapon::Shoot()
{
	for (auto go : RenderQueue::Instance()->RenderableObjects)
	{
		if (Collision::RayCastCheck(gunray, go->collider))
		{
			printf("CollisionHit");
			if (go->Tag == "Target")
			{
				go->DestoryObject();
			}

		}
	}
}
