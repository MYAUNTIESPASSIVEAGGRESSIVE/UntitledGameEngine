#pragma once
#include <memory>
#include <string>
#include "Transform.h"

class DXMaterial;

class DXMesh;

class GameObject
{
public:

	Transform transform;

	std::string GetName() { return objectName; };

	GameObject(std::string objectName, std::shared_ptr<DXMesh> objectMesh, DXMaterial* objMaterial);

	void SetParent(GameObject* parent);

	GameObject* GetParent() { return parentObject; }

	std::shared_ptr<DXMesh> GetObjectMesh() { return ObjectMesh; }
	DXMaterial* GetObjectMaterial() { return ObjectMaterial; }

	DXMesh* SetObjectMesh(DXMesh* inMesh);
	//DXMaterial* SetObjectMaterial()


	private:

	std::string objectName = "GameObject";

	GameObject* parentObject = nullptr;

	std::shared_ptr<DXMesh> ObjectMesh;

	DXMaterial* ObjectMaterial;
};

