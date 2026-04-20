#include "Object.h"

Object::Object(std::string name)
	: objectName(name)
{

}

void Object::SetParent(Object* parent)
{
	DirectX::XMVectorSubtract(transform.position, parent->transform.position);

	parentObject = parent;
}
