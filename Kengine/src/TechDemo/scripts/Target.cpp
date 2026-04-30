#include "Target.h"

void Target::Update()
{
	if (health <= 0.0f)
	{
		GameObject::DestoryObject();
	}
}
