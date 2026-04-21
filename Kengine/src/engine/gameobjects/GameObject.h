#pragma once
#include "Object.h"

class DXMaterial;

class DXMesh;

class GameObject :
	public Object
{
public:

	GameObject(std::string objectName, DXMesh* objectMesh, DXMaterial* objMaterial);

	DXMesh* GetObjectMesh() { return ObjectMesh; }
	DXMaterial* GetObjectMaterial() { return ObjectMaterial; }

	void CompareMaterial();

private:

	DXMesh* ObjectMesh;

	DXMaterial* ObjectMaterial;
};

