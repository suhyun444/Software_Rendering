#include "Camera.h"

const int KeyCodeA = 0x41;
const int KeyCodeS = 0x53;
const int KeyCodeD = 0x44;
const int KeyCodeW = 0x57;
const int KeyCodeQ = 0x51;
const int KeyCodeE = 0x45;
const int KeyCodeLeftArrow = VK_LEFT;
const int KeyCodeDownArrow = VK_DOWN;
const int KeyCodeRightArrow = VK_RIGHT;
const int KeyCodeUpArrow = VK_UP;
Camera::Camera(float nearPlane, float farPlane,float aspect,float fov)
{
	this->position = Vector3(0, 0, -10.0);
	this->rotation = Vector3(0, 0, 0);
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	this->aspect = aspect;
	this->fov = fov;
}
Camera::~Camera()
{


}
void Camera::UpdateViewMatrix()
{
	viewMatrix = Matrix4x4::GetModelMatrix(Vector3(1, 1, 1), rotation, position).Inverse();
}


void Camera::UpdateProjectionMatrix()
{
	float top = nearPlane * tanf(3.1415f / 180 * fov / 2);
	float right = top * aspect;
	float m11 = nearPlane / right;
	float m22 = nearPlane / top;
	float m33 = (farPlane + nearPlane) / (nearPlane - farPlane);
	float m34 = (2 * farPlane * nearPlane) / (nearPlane - farPlane);
	projectionMatrix.M11 = m11; projectionMatrix.M12 = 0;	projectionMatrix.M13 = 0;		projectionMatrix.M14 = 0;
	projectionMatrix.M21 = 0;	projectionMatrix.M22 = m22;	projectionMatrix.M23 = 0  ;		projectionMatrix.M24 = 0;
	projectionMatrix.M31 = 0;	projectionMatrix.M32 = 0;	projectionMatrix.M33 = m33;		projectionMatrix.M34 = m34;
	projectionMatrix.M41 = 0;	projectionMatrix.M42 = 0;	projectionMatrix.M43 = -1;		projectionMatrix.M44 = 0;
}

void Camera::UpdateViewingVector()
{
	Vector4 viewingVector4 = Vector4(0, 0, 1, 0);
	viewingVector4 = Matrix4x4::GetModelMatrix(Vector3(1, 1, 1), rotation, position) * viewingVector4;
	viewingVector = Vector3(viewingVector4.x, viewingVector4.y, viewingVector4.z);
}
Vector3 Camera::GetHorizontalVector()
{
	Vector4 upVector4 = Vector4(0,1,0,0);
	upVector4 = Matrix4x4::GetModelMatrix(Vector3(1, 1, 1), rotation, position) * upVector4;
	Vector3 upVector = Vector3(upVector4.x,upVector4.y,upVector4.z);
	return viewingVector.Cross(upVector);
}
Vector3 Camera::GetVerticalVector()
{
	Vector4 rightVector4 = Vector4(1, 0, 0, 0);
	rightVector4 = Matrix4x4::GetModelMatrix(Vector3(1, 1, 1), rotation, position) * rightVector4;
	Vector3 rightVector = Vector3(rightVector4.x, rightVector4.y, rightVector4.z);
	return viewingVector.Cross(rightVector);
}
void Camera::Move()
{
	Vector3 horizontalVector = GetHorizontalVector();
	Vector3 verticalVector = GetVerticalVector();
	if(InputController::GetKeyDown(KeyCodeA))position -= horizontalVector * 10.0f * Time::GetDeltaTime();
	if(InputController::GetKeyDown(KeyCodeD))position += horizontalVector * 10.0f * Time::GetDeltaTime();
	if(InputController::GetKeyDown(KeyCodeS))position -= verticalVector * 10.0f * Time::GetDeltaTime();
	if(InputController::GetKeyDown(KeyCodeW))position += verticalVector * 10.0f * Time::GetDeltaTime();
	if(InputController::GetKeyDown(KeyCodeE))position -= viewingVector * 10.0f * Time::GetDeltaTime();
	if(InputController::GetKeyDown(KeyCodeQ))position += viewingVector * 10.0f * Time::GetDeltaTime();

	if(InputController::GetKeyDown(KeyCodeLeftArrow))rotation.y += 60.0f * Time::GetDeltaTime();
	if(InputController::GetKeyDown(KeyCodeRightArrow))rotation.y -= 60.0f * Time::GetDeltaTime();
	if (InputController::GetKeyDown(KeyCodeUpArrow))rotation.x -= 60.0f * Time::GetDeltaTime();
	if (InputController::GetKeyDown(KeyCodeDownArrow))rotation.x += 60.0f * Time::GetDeltaTime();
}
void Camera::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
	UpdateViewingVector();
	Move();
}