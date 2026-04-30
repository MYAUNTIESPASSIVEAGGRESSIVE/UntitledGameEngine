#include "Collision.h"
#include "engine/gameobjects/GameObject.h"

// circle vs circle collision check
bool Collision::OnSphereCollide(SphereCollider c1, SphereCollider c2)
{
	float dx = XMVectorGetX(c2.transform.position) - XMVectorGetX(c1.transform.position);
	float dy = XMVectorGetY(c2.transform.position) - XMVectorGetY(c1.transform.position);
	float dz = XMVectorGetZ(c2.transform.position) - XMVectorGetZ(c1.transform.position);

	float distance = sqrt((dx * dx) + (dy * dy) + (dz * dz));

	return distance <= c1.radius + c2.radius ? true : false;
}

// AABB vs AABB collision check
bool Collision::OnBoxCollide(BoxCollider box1, BoxCollider box2)
{
	return (box1.minX <= box2.maxX &&
		box1.maxX >= box2.minX &&
		box1.minY <= box2.maxY &&
		box1.maxY >= box2.minY &&
		box1.minZ <= box2.maxZ &&
		box1.maxZ >= box2.minZ);
}

// Box vs Cricle Collision
bool Collision::OnBoxVCircleCollide(BoxCollider box, SphereCollider circle)
{
	float x = fmax(box.minX, fmin(XMVectorGetX(circle.transform.position), box.maxX));
	float y = fmax(box.minY, fmin(XMVectorGetY(circle.transform.position), box.maxX));
	float z = fmax(box.minZ, fmin(XMVectorGetZ(circle.transform.position), box.maxX));

	float distance = sqrt(
		(x - XMVectorGetX(circle.transform.position) * x - XMVectorGetX(circle.transform.position)) +
		(y - XMVectorGetY(circle.transform.position) * y - XMVectorGetY(circle.transform.position)) +
		(z - XMVectorGetZ(circle.transform.position) * z - XMVectorGetZ(circle.transform.position))
	);

	return distance < circle.radius ? true : false;
}

bool Collision::OnCollide(GameObject obj1, GameObject obj2)
{
	if (obj1.collider.Type == ColliderType::BOX && obj2.collider.Type == ColliderType::BOX)
	{
		return OnBoxCollide(obj1.collider.boxCollider, obj2.collider.boxCollider);
	}
	else if(obj1.collider.Type == ColliderType::SPHERE && obj2.collider.Type == ColliderType::SPHERE)
	{
		return OnSphereCollide(obj1.collider.sphereCollider, obj2.collider.sphereCollider);
	}
	else
	{
		if (obj1.collider.Type == ColliderType::BOX) return OnBoxVCircleCollide(obj1.collider.boxCollider, obj2.collider.sphereCollider);
		else return OnBoxVCircleCollide(obj2.collider.boxCollider, obj1.collider.sphereCollider);
	}
}

