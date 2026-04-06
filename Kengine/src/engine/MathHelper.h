#pragma once
#include <math.h>
#define PI 3.14159265
#define DEG_TO_RAD PI/180.0f

namespace Kengine
{
#pragma region Vectors

	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
			:x(_x), y(_y), z(_z) {
		}

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

	// rotation of a vector 3 by an angle (float) TODO ADD V3Z
	inline Vector3 Vector3AddAngles(Vector3& vector, float angle)
	{
		float radAngle = (float)(angle * DEG_TO_RAD);

		return Vector3(
			(float)(vector.x * cos(radAngle) - vector.y * sin(radAngle)),
			(float)(vector.x * sin(radAngle) + vector.y * cos(radAngle)));
	}

	//inline Vector3 Vector3AddQuaternion(Vector3& vector, Quaternion& quaternion)
	//{
	//	// add quaternion rotation here
	//}

	//inline Vector3 Vector3AddMatrix(Vector3& vector, Matrix& matrix)
	//{
	//	// add matrix rotation here
	//}

	inline Vector3 CrossProduct(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 result
		{
			(lhs.y * rhs.z) - (lhs.z * rhs.y),
			(lhs.z * rhs.x) - (lhs.x * rhs.z),
			(lhs.x * rhs.y) - (lhs.y * rhs.x),
		};

		return result;
	}

	inline Vector3 DotProduct(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 result
		{
			lhs.x * rhs.x,
			lhs.y * rhs.y,
			lhs.z * rhs.z,
		};
	}

	inline float Distance(Vector3 v1, Vector3 v2)
	{
		float dx = v2.x - v1.x;
		float dy = v2.y - v1.y;
		float dz = v2.z - v1.z;

		return sqrt((dx * dx) + (dy * dy) + (dz * dz));
	}

#pragma endregion

#pragma region Vector2

	struct Vector2
	{
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f)
			:x(_x), y(_y) {
		}

		float MagnitudeSqr()
		{
			return x * x + y * y;
		}

		float Magnitude()
		{
			return (float)sqrt(x * x + y * y);
		}

		Vector2 Normalized()
		{
			float mag = Magnitude();

			return Vector2(x / mag, y / mag);
		}

		Vector2& operator +=(const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}


		Vector2& operator -=(const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}
	};

	// addition of two vectors (left added by right)
	inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	// subtraction of two vectors (left subtracted by right)
	inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	// Multiplication of two vectors (left multiplied by right)
	inline Vector2 operator *(const Vector2& lhs, const float& rhs)
	{
		return Vector2(lhs.x * rhs, lhs.y * rhs);
	}

#pragma endregion

#pragma region Matricies

	struct Matrix
	{
		float m[4][4]
		{
			_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44,
		};

		Vector3 vm[4];
	};

	inline Matrix operator+(const Matrix& lhs, const Matrix& rhs)
	{
		Matrix result
		{
			lhs.m[1][1] + rhs.m[1][1], lhs.m[1][2] + rhs.m[1][2], lhs.m[1][3] + rhs.m[1][3], lhs.m[1][4] + rhs.m[1][4],
			lhs.m[2][1] + rhs.m[2][1], lhs.m[2][2] + rhs.m[2][2], lhs.m[2][3] + rhs.m[2][3], lhs.m[2][4] + rhs.m[2][4],
			lhs.m[3][1] + rhs.m[3][1], lhs.m[3][2] + rhs.m[3][2], lhs.m[3][3] + rhs.m[3][3], lhs.m[3][4] + rhs.m[3][4],
			lhs.m[4][1] + rhs.m[4][1], lhs.m[4][2] + rhs.m[4][2], lhs.m[4][3] + rhs.m[4][3], lhs.m[4][4] + rhs.m[4][4],
		};

		return result;
	}

	inline Matrix operator-(const Matrix& lhs, const Matrix& rhs)
	{
		Matrix result
		{
			lhs.m[1][1] - rhs.m[1][1], lhs.m[1][2] - rhs.m[1][2], lhs.m[1][3] - rhs.m[1][3], lhs.m[1][4] - rhs.m[1][4],
			lhs.m[2][1] - rhs.m[2][1], lhs.m[2][2] - rhs.m[2][2], lhs.m[2][3] - rhs.m[2][3], lhs.m[2][4] - rhs.m[2][4],
			lhs.m[3][1] - rhs.m[3][1], lhs.m[3][2] - rhs.m[3][2], lhs.m[3][3] - rhs.m[3][3], lhs.m[3][4] - rhs.m[3][4],
			lhs.m[4][1] - rhs.m[4][1], lhs.m[4][2] - rhs.m[4][2], lhs.m[4][3] - rhs.m[4][3], lhs.m[4][4] - rhs.m[4][4],
		};

		return result;
	}

	inline Matrix operator*(const Matrix& lhs, const Matrix& rhs)
	{
		Matrix result
		{
			(lhs.m[1][1] * rhs.m[1][1]) + (lhs.m[1][2] * rhs.m[2][1]) + (lhs.m[1][3] * rhs.m[3][1]) + (lhs.m[1][4] * rhs.m[4][1]),
			(lhs.m[1][1] * rhs.m[1][2]) + (lhs.m[1][2] * rhs.m[2][2]) + (lhs.m[1][3] * rhs.m[3][2]) + (lhs.m[1][4] * rhs.m[4][2]),
			(lhs.m[1][1] * rhs.m[1][3]) + (lhs.m[1][2] * rhs.m[2][3]) + (lhs.m[1][3] * rhs.m[3][3]) + (lhs.m[1][4] * rhs.m[4][3]),
			(lhs.m[1][1] * rhs.m[1][3]) + (lhs.m[1][2] * rhs.m[2][4]) + (lhs.m[1][3] * rhs.m[3][4]) + (lhs.m[1][4] * rhs.m[4][4]),

			(lhs.m[2][1] * rhs.m[1][1]) + (lhs.m[2][2] * rhs.m[2][1]) + (lhs.m[2][3] * rhs.m[3][1]) + (lhs.m[2][4] * rhs.m[4][1]),
			(lhs.m[2][1] * rhs.m[1][2]) + (lhs.m[2][2] * rhs.m[2][2]) + (lhs.m[2][3] * rhs.m[3][2]) + (lhs.m[2][4] * rhs.m[4][2]),
			(lhs.m[2][1] * rhs.m[1][3]) + (lhs.m[2][2] * rhs.m[2][3]) + (lhs.m[2][3] * rhs.m[3][3]) + (lhs.m[2][4] * rhs.m[4][3]),
			(lhs.m[2][1] * rhs.m[1][3]) + (lhs.m[2][2] * rhs.m[2][4]) + (lhs.m[2][3] * rhs.m[3][4]) + (lhs.m[2][4] * rhs.m[4][4]),

			(lhs.m[3][1] * rhs.m[1][1]) + (lhs.m[3][2] * rhs.m[2][1]) + (lhs.m[3][3] * rhs.m[3][1]) + (lhs.m[3][4] * rhs.m[4][1]),
			(lhs.m[3][1] * rhs.m[1][2]) + (lhs.m[3][2] * rhs.m[2][2]) + (lhs.m[3][3] * rhs.m[3][2]) + (lhs.m[3][4] * rhs.m[4][2]),
			(lhs.m[3][1] * rhs.m[1][3]) + (lhs.m[3][2] * rhs.m[2][3]) + (lhs.m[3][3] * rhs.m[3][3]) + (lhs.m[3][4] * rhs.m[4][3]),
			(lhs.m[3][1] * rhs.m[1][3]) + (lhs.m[3][2] * rhs.m[2][4]) + (lhs.m[3][3] * rhs.m[3][4]) + (lhs.m[3][4] * rhs.m[4][4]),

			(lhs.m[4][1] * rhs.m[1][1]) + (lhs.m[4][2] * rhs.m[2][1]) + (lhs.m[4][3] * rhs.m[3][1]) + (lhs.m[4][4] * rhs.m[4][1]),
			(lhs.m[4][1] * rhs.m[1][2]) + (lhs.m[4][2] * rhs.m[2][2]) + (lhs.m[4][3] * rhs.m[3][2]) + (lhs.m[4][4] * rhs.m[4][2]),
			(lhs.m[4][1] * rhs.m[1][3]) + (lhs.m[4][2] * rhs.m[2][3]) + (lhs.m[4][3] * rhs.m[3][3]) + (lhs.m[4][4] * rhs.m[4][3]),
			(lhs.m[4][1] * rhs.m[1][3]) + (lhs.m[4][2] * rhs.m[2][4]) + (lhs.m[4][3] * rhs.m[3][4]) + (lhs.m[4][4] * rhs.m[4][4]),
		};

		return result;
	}

	inline Matrix ScaleFromVector(Vector3 scale)
	{
		Matrix M;
		M.m[0][0] = { scale.x };
		M.m[0][1] = 0.0f;
		M.m[0][2] = 0.0f;
		M.m[0][3] = 0.0f;

		M.m[1][0] = 0.0f;
		M.m[1][1] = { scale.y };
		M.m[1][2] = 0.0f;
		M.m[1][3] = 0.0f;

		M.m[2][0] = 0.0f;
		M.m[2][1] = 0.0f;
		M.m[2][2] = { scale.x };
		M.m[2][3] = 0.0f;


		M.m[3][0] = 0.0f;
		M.m[3][1] = 0.0f;
		M.m[3][2] = 0.0f;
		M.m[3][3] = 1.0f;
	}

	inline Matrix RotationFromVector(Vector3 rotation)
	{
		float cp = cosf(rotation.x);
		float sp = sinf(rotation.x);

		float cy = cosf(rotation.y);
		float sy = sinf(rotation.y);

		float cr = cosf(rotation.z);
		float sr = sinf(rotation.z);

		Matrix M;
		M.m[0][0] = cr * cy + sr * sp * sy;
		M.m[0][1] = sr * cp;
		M.m[0][2] = sr * sp * cy - cr * sy;
		M.m[0][3] = 0.0f;

		M.m[1][0] = cr * sp * sy - sr * cy;
		M.m[1][1] = cr * cp;
		M.m[1][2] = sr * sy + cr * sp * cy;
		M.m[1][3] = 0.0f;

		M.m[2][0] = cp * sy;
		M.m[2][1] = -sp;
		M.m[2][2] = cp * cy;
		M.m[2][3] = 0.0f;

		M.m[3][0] = 0.0f;
		M.m[3][1] = 0.0f;
		M.m[3][2] = 0.0f;
		M.m[3][3] = 1.0f;
		return M;
	}

	inline Matrix TranslateFromVector(Vector3 position)
	{
		Matrix M;
		M.m[0][0] = 1.0f;
		M.m[0][1] = 0.0f;
		M.m[0][2] = 0.0f;
		M.m[0][3] = 0.0f;

		M.m[1][0] = 0.0f;
		M.m[1][1] = 1.0f;
		M.m[1][2] = 0.0f;
		M.m[1][3] = 0.0f;

		M.m[2][0] = 0.0f;
		M.m[2][1] = 0.0f;
		M.m[2][2] = 1.0f;
		M.m[2][3] = 0.0f;

		M.m[3][0] = position.x;
		M.m[3][1] = position.y;
		M.m[3][2] = position.z;
		M.m[3][3] = 1.0f;
		return M;
	}

#pragma endregion

#pragma region Quaternions

	struct Quaternion
	{
		float x;
		float y;
		float z;
		float w;

		Quaternion(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
			: x(_x), y(_y), z(_z), w(_w) {

		}



	};

#pragma endregion


#pragma region CollisionMaths



#pragma endregion

}