#pragma once
#include <memory>
#include <string>
#include "Transform.h"

namespace Kengine
{
	class DXMaterial;

	class DXMesh;

	class GameObject
	{
	public:

		Transform transform;

		std::string GetName() { return objectName; }

		GameObject(std::string objectName, DXMesh* objectMesh, DXMaterial* objMaterial);

		void SetParent(GameObject* parent);

		GameObject* GetParent() { return parentObject; }

		DXMesh* GetObjectMesh() { return ObjectMesh; }
		DXMaterial* GetObjectMaterial() { return ObjectMaterial; }

		DXMesh* SetObjectMesh(DXMesh* inMesh);
		DXMaterial* SetObjectMaterial();


	private:

		std::string objectName = "GameObject";

		GameObject* parentObject;

		DXMesh* ObjectMesh;

		DXMaterial* ObjectMaterial;
	};
}


