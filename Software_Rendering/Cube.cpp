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
void Cube::UpdateTransform(Camera camera)
{
	Matrix4x4 t = camera.GetProjectionMatrix() * camera.GetViewMatrix() * Matrix4x4::GetModelMatrix(scale, rotation, position);
	for (int i = 0; i < 8; i++)
	{
		Vector4 p = Vector4(vertices[i]);
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
bool Cube::DontNeedToDraw(Vector3 viewingVector,Vector3 p1,Vector3 p2,Vector3 p3)
{
	Vector3 s1 = p1 - p2;
	Vector3 s2 = p3 - p2;
	Vector3 normal = s1.Cross(s2);
	return normal.Dot(viewingVector) < 0;
}
void Cube::Draw(HDC hdc, Camera camera)
{
	for (int i = 0; i < 12; i++)
	{
		// back-face culling
		Vector3 p1 = deviceCoordinateVertices[indices[i]._1];
		Vector3 p2 = deviceCoordinateVertices[indices[i]._2];
		Vector3 p3 = deviceCoordinateVertices[indices[i]._3];

		if(DontNeedToDraw(camera.GetViewingVector(),p1,p2,p3))continue;

		// draw
		MoveToEx(hdc, p1.x, p1.y, NULL);
		LineTo(hdc, p2.x, p2.y);

		MoveToEx(hdc, p2.x, p2.y, NULL);
		LineTo(hdc, p3.x, p3.y);

		MoveToEx(hdc, p3.x, p3.y, NULL);
		LineTo(hdc, p1.x, p1.y);
	}
}