#pragma once
#include "math.h"

class Camera
{
private:
	float nearPlane;
	float farPlane;
	float aspect;
	float fov;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
public:
	Vector3 position;
	Vector3 rotation;
	Camera(float nearPlane,float farPlane,float aspect,float fov);
	~Camera();
	void SetViewMatrix();
	Matrix4x4 GetViewMatrix() { return viewMatrix; }
	void SetProjectionMatrix();
	Matrix4x4 GetProjectionMatrix() { return projectionMatrix; }
};

