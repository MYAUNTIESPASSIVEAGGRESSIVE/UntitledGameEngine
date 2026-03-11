#pragma once
#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI/180.0f

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(float _x = 0.0f,float _y = 0.0f, float _z = 0.0f)
		:x(_x), y(_y), z(_z) { }

	float MagnitudeSqr()
	{
		return x * x + y * y + z * z;
	}

	float Magnitude()
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	Vector3 Normalized()
	{
		float mag = Magnitude();

		return Vector3(x / mag, y / mag, z / mag);
	}

	Vector3& operator +=(const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}


	Vector3& operator -=(const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}
};

// addition of two vectors (left added by right)
inline Vector3 operator +(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

// subtraction of two vectors (left subtracted by right)
inline Vector3 operator -(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

// Multiplication of two vectors (left multiplied by right)
inline Vector3 operator *(const Vector3& lhs, const float& rhs)
{
	return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

// rotation of a vector 3 by an angle (float)
inline Vector3 RotateVector3(Vector3& vector, float angle)
{
	
}