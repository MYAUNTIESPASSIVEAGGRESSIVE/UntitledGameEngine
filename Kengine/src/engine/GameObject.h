#pragma once
#include <string>
#include "Transform.h"

namespace Kengine
{
	class GameObject
	{
	public:

		Transform transform;

		std::string GetName() { return objectName; }

		GameObject(std::string objectName);

		void SetParent(GameObject* parent);

		GameObject* GetParent() { return parentObject; }

	private:

		std::string objectName = "GameObject";

		GameObject* parentObject;
	};
}


