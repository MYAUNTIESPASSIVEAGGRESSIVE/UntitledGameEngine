#pragma once
#include <string>
#include "Transform.h"

class Object
{
public:

	Object(std::string name);

	std::string GetName() { return objectName; };

	Transform transform;

	Object* GetParent() { return parentObject; }

	void SetParent(Object* parent);

protected:

	std::string objectName;

private:

	Object* parentObject = nullptr;

};