#include "Cube.h"
Cube::Cube()
{
	scale = Vector3(1, 1, 1);
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);

	vertices[0] = Vector3(-1, 1, 1);
	vertices[1] = Vector3(1, 1, 1);
	vertices[2] = Vector3(1, 1, -1);	
	vertices[3] = Vector3(-1, 1, -1);

	vertices[4] = Vector3(-1, -1, 1);
	vertices[5] = Vector3(1, -1, 1);
	vertices[6] = Vector3(1, -1, -1);
	vertices[7] = Vector3(-1, -1, -1);

	indices[0]  = Index(0, 1, 2); indices[1]  = Index(0, 2, 3);
	indices[2]  = Index(0, 3, 7); indices[3]  = Index(0, 7, 4);
	indices[4]  = Index(3, 2, 6); indices[5]  = Index(3, 6, 7);
	indices[6]  = Index(2, 1, 5); indices[7]  = Index(2, 5, 6);
	indices[8]  = Index(1, 0, 4); indices[9]  = Index(1, 4, 5);
	indices[10] = Index(7, 6, 5); indices[11] = Index(7, 5, 4);
}

Matrix4x4 Cube::GetModelMatrix()
{
	return Matrix4x4::GetModelMatrix(scale, rotation, position);
}
void Cube::UpdateTransform(const Camera& camera)
{
	Matrix4x4 modelMatrix = Matrix4x4::GetModelMatrix(scale, rotation, position);
	Matrix4x4 t = camera.GetProjectionMatrix() * camera.GetViewMatrix() * modelMatrix;
	for (int i = 0; i < 8; i++)
	{
		Vector4 p = Vector4(vertices[i]);
		
		Vector4 vWcs = Matrix4x4::GetModelMatrix(scale, rotation, position) * p;
		worldCoordinateVertices[i] = Vector3(vWcs.x,vWcs.y,vWcs.z);
		
		Vector4 vNdcs = t * p;
		// Clipping coordinate system -> Normalized device coordinate system
		deviceCoordinateVertices[i] = Vector3(vNdcs.x / vNdcs.w, vNdcs.y / vNdcs.w, vNdcs.z / vNdcs.w);
		// Normalized device coordinate system -> Device coordinate system
		deviceCoordinateVertices[i].x += 1;
		deviceCoordinateVertices[i].x *= (float)Window::width / 2.0f;
		deviceCoordinateVertices[i].y += 1;
		deviceCoordinateVertices[i].y *= (float)Window::height / 2.0f;
	}

}
// https://velog.io/@jaehyeoksong0/graphics-3
// TODO : BackfaceCulling 최적화하기
bool Cube::DontNeedToDraw(Vector3 viewingVector,int index)
{
	Vector3 v1 = worldCoordinateVertices[indices[index]._1], v2 = worldCoordinateVertices[indices[index]._2], v3 = worldCoordinateVertices[indices[index]._3];
	Vector3 s1 = v1 - v2;
	Vector3 s2 = v3 - v2;
	Vector3 normal = s1.Cross(s2);
	return normal.Dot(viewingVector) < 0;
}
void Cube::Draw(const HDC& hdc, const Camera& camera)
{
	for (int i = 0; i < 12; i++)
	{
		// back-face culling
		if(DontNeedToDraw(position -  camera.position,i))continue;

		Vector3 p1 = deviceCoordinateVertices[indices[i]._1];
		Vector3 p2 = deviceCoordinateVertices[indices[i]._2];
		Vector3 p3 = deviceCoordinateVertices[indices[i]._3];

		Draw::DrawTriangle(hdc,p1,p2,p3);
	}
}