#pragma once
#include "math.h"
#include <Windows.h>

class Cube
{
private:
public:
	Vector3 scale;
	Vector3 rotation;
	Vector3 position;
	Vector3 vertices[8];
	Vector3 deviceCoordinateVertices[8];
	Index indices[12];
	Cube();
	Matrix4x4 GetModelMatrix();

};

