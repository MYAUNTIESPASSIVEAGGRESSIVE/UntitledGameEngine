#include "Target.h"

Target::Target(std::string name, std::string tag, DXMesh* mesh,
	DXMaterial* material, ColliderType type,bool simulatephysics, float rad)
	: GameObject(name, tag, mesh, material, type, simulatephysics, rad)
{

}

void Target::Update()
{
	if (health <= 0.0f)
	{
		GameObject::DestoryObject();
	}
}
