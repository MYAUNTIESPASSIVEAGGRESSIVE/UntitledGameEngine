#include "Object.h"

Object::Object(std::string name, std::string tag)
	: objectName(name), Tag(tag)
{

}

void Object::SetParent(Object* parent)
{
	DirectX::XMVectorSubtract(transform.position, parent->transform.position);

	parentObject = parent;
}
