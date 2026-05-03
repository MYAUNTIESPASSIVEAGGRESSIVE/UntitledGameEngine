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

	void UpdateChildPosition(DirectX::XMVECTOR pos, DirectX::XMVECTOR rot)
	{
		if (parentObject != nullptr)
		{
			transform.rotation = rot;
			transform.position = pos;
		}
	}

	std::string Tag;

protected:

	std::string objectName;

private:

	Object* parentObject = nullptr;

};