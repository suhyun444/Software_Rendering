#pragma once
#include "math.h"
#include "InputController.h"
#include "Time.h"

class Camera
{
private:
	float nearPlane;
	float farPlane;
	float aspect;
	float fov;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Vector3 viewingVector;
	Vector3 GetHorizontalVector();
	Vector3 GetVerticalVector();
public:
	Vector3 position;
	Vector3 rotation;
	Camera(float nearPlane,float farPlane,float aspect,float fov);
	~Camera();
	void Update();
	void UpdateViewMatrix();
	Matrix4x4 GetViewMatrix() { return viewMatrix; }
	void UpdateProjectionMatrix();
	Matrix4x4 GetProjectionMatrix() { return projectionMatrix; }
	void UpdateViewingVector();
	Vector3 GetViewingVector() { return viewingVector; }
	void Move();
};


