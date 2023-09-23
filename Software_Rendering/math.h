#pragma once
#include <math.h>
#include <utility>

class Math
{
public:
	template <typename T>
	static T Min(const T &a, const T &b){return (a < b) ? a : b;}
	template <typename T>
	static T Max(const T &a, const T &b){return (a > b) ? a : b;}
};
class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3 operator+(const Vector3& v);
	Vector3 operator-(const Vector3 &v);
	Vector3 operator+=(const Vector3 &v);
	Vector3 operator-=(const Vector3 &v);
	Vector3 operator*(float other);
	Vector3 Reverse();
	float Dot(Vector3& v);
	Vector3 Cross(Vector3& v);
	Vector3 Normalize();
};

class Vector4
{
public:
	float x, y, z, w;
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 v);
	Vector4 operator+(const Vector4 &v);
	Vector4 operator-(const Vector4 &v);
	float Dot(Vector4& v);
};

class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float x, float y);
	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2 &v);
	float Dot(Vector2& v);
};

class Matrix4x4
{
public:
	float M11, M12, M13, M14;
	float M21, M22, M23, M24;
	float M31, M32, M33, M34;
	float M41, M42, M43, M44;
	Matrix4x4();
	Matrix4x4(float M11, float M12, float M13, float M14,
		float M21, float M22, float M23, float M24,
		float M31, float M32, float M33, float M34,
		float M41, float M42, float M43, float M44);
	Matrix4x4 operator+(const Matrix4x4 &m);
	Matrix4x4 operator-(const Matrix4x4 &m);
	Matrix4x4 operator*(const Matrix4x4 m);
	Matrix4x4 Multiply(Matrix4x4 m);
	Vector4 operator*(const Vector4 &v);
	Matrix4x4 Inverse();
	static Matrix4x4 Translate(Vector3 position);
	static Matrix4x4 RotationX(float angle);
	static Matrix4x4 RotationY(float angle);
	static Matrix4x4 RotationZ(float angle);
	static Matrix4x4 Rotation(Vector3 rotation);
	static Matrix4x4 Scale(Vector3 scale);
	static Matrix4x4 GetModelMatrix(Vector3 scale, Vector3 rotation, Vector3 position);
};

struct Index
{
	unsigned int _1, _2, _3;
	Index();
	Index(unsigned int _1, unsigned int _2, unsigned int _3);
};
