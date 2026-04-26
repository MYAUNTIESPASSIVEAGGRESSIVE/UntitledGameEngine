#include "Collision.h"
#include "engine/gameobjects/GameObject.h"

// circle vs circle collision check
bool Collision::OnSphereCollide(SphereCollider c1, SphereCollider c2)
{
	float dx = XMVectorGetX(c2.circleVector) - XMVectorGetX(c1.circleVector);
	float dy = XMVectorGetY(c2.circleVector) - XMVectorGetY(c1.circleVector);
	float dz = XMVectorGetZ(c2.circleVector) - XMVectorGetZ(c1.circleVector);

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
	float x = fmax(box.minX, fmin(XMVectorGetX(circle.circleVector), box.maxX));
	float y = fmax(box.minY, fmin(XMVectorGetY(circle.circleVector), box.maxX));
	float z = fmax(box.minZ, fmin(XMVectorGetZ(circle.circleVector), box.maxX));

	float distance = sqrt(
		(x - XMVectorGetX(circle.circleVector) * x - XMVectorGetX(circle.circleVector)) +
		(y - XMVectorGetY(circle.circleVector) * y - XMVectorGetY(circle.circleVector)) +
		(z - XMVectorGetZ(circle.circleVector) * z - XMVectorGetZ(circle.circleVector))
	);

	return distance < circle.radius ? true : false;
}

