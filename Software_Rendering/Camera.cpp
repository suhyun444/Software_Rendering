#include "Camera.h"

Camera::Camera(float nearPlane, float farPlane,float aspect,float fov)
{
	this->position = Vector3(0, 0, 0);
	this->rotation = Vector3(0, 0, 0);
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	this->aspect = aspect;
	this->fov = fov;
}
Camera::~Camera()
{


}
void Camera::SetViewMatrix()
{
	viewMatrix = Matrix4x4::GetModelMatrix(Vector3(1, 1, 1), rotation, position).Inverse();
}

void Camera::SetProjectionMatrix()
{
	float top = nearPlane * tanf(3.1415f / 180 * fov / 2);
	float bottom = -top;
	float right = top * aspect;
	float left = -right;
	float m11 = nearPlane / right;
	float m22 = nearPlane / top;
	float m33 = (farPlane + nearPlane) / (nearPlane - farPlane);
	float m34 = (2 * farPlane * nearPlane) / (nearPlane - farPlane);
	projectionMatrix.M11 = m11; projectionMatrix.M12 = 0;	projectionMatrix.M13 = 0;		projectionMatrix.M14 = 0;
	projectionMatrix.M21 = 0;	projectionMatrix.M22 = m22;	projectionMatrix.M23 = 0  ;		projectionMatrix.M24 = 0;
	projectionMatrix.M31 = 0;	projectionMatrix.M32 = 0;	projectionMatrix.M33 = m33;		projectionMatrix.M34 = m34;
	projectionMatrix.M41 = 0;	projectionMatrix.M42 = 0;	projectionMatrix.M43 = -1;		projectionMatrix.M44 = 0;
}