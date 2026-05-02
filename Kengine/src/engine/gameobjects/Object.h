#pragma once
#include <string>
#include "Transform.h"

class Object
{
public:

	Object(std::string name = NULL, std::string tag = NULL);

	std::string GetName() { return objectName; };

	Transform transform;

	Object* GetParent() { return parentObject; }

	void SetParent(Object* parent);

	void UpdateChildPosition()
	{
		if(parentObject != nullptr) transform.position = parentObject->transform.position;
	}

	std::string Tag;

protected:

	std::string objectName;

private:

	Object* parentObject = nullptr;

};