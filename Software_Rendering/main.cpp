#include "Window.h"
#include "math.h"
#include "Cube.h"
#include "Camera.h"
#include "Timer.h"
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define FPS 1/60

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	Window window = Window(hInstance, 1280, 720, L"SoftwareRendering");
	if (window.InitializeWindow() == false)
	{
		MessageBoxW(nullptr, L"InitializeWindow Failed", L"Error", 0);
		exit(-1);
	}
	HDC hdc = GetDC(window.GetHWND());

	//카메라 생성
	float width = window.GetWidth();
	float height = window.GetHeight();
	float aspect = width / height;
	Camera camera = Camera(0.1f, 100, aspect, 70);
	camera.position = Vector3(0, 0, 0);

	//큐브 생성
	Cube c;
	c.scale = Vector3(1, 1, 1);
	c.rotation = Vector3(-30, -30, 0);
	c.position = Vector3(0, 0, 10);

	//MVP Transform 행렬 만들기
	camera.SetViewMatrix();
	Matrix4x4 a = camera.GetViewMatrix();
	camera.SetProjectionMatrix();
	Matrix4x4 t = camera.GetProjectionMatrix() * camera.GetViewMatrix() * Matrix4x4::GetModelMatrix(c.scale, c.rotation, c.position);
	for (int i = 0; i < 8; i++)
	{
		Vector4 p = Vector4(c.vertices[i]);
		Vector4 vNdcs = t * p;
		//Clipping coordinate system -> Normalized device coordinate system
		c.deviceCoordinateVertices[i] = Vector3(vNdcs.x / vNdcs.w, vNdcs.y / vNdcs.w, vNdcs.z / vNdcs.w);
		//Normalized device coordinate system -> Device coordinate system
		c.deviceCoordinateVertices[i].x += 1;
		c.deviceCoordinateVertices[i].x *= (float)window.GetWidth() / 2.0f;
		c.deviceCoordinateVertices[i].y += 1;
		c.deviceCoordinateVertices[i].y *= (float)window.GetHeight() / 2.0f;
	}
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	Timer timer;
	if (!timer.Initialize())return 0;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (timer.GetTime() > 1000 / 60)
			{
				BitBlt(hdc, 0, 0, window.GetWidth(), window.GetHeight(), 0, 0, 0, WHITENESS);
				std::cout << timer.GetTime() << "\n";
				c.rotation.y += 0.1f * timer.GetTime();
				camera.SetViewMatrix();
				Matrix4x4 a = camera.GetViewMatrix();
				camera.SetProjectionMatrix();
				//mvp transform
				Matrix4x4 t = camera.GetProjectionMatrix() * camera.GetViewMatrix() * Matrix4x4::GetModelMatrix(c.scale, c.rotation, c.position);
				for (int i = 0; i < 8; i++)
				{
					Vector4 p = Vector4(c.vertices[i]);
					Vector4 vNdcs = t * p;
					//Clipping coordinate system -> Normalized device coordinate system
					c.deviceCoordinateVertices[i] = Vector3(vNdcs.x / vNdcs.w, vNdcs.y / vNdcs.w, vNdcs.z / vNdcs.w);
					//Normalized device coordinate system -> Device coordinate system
					c.deviceCoordinateVertices[i].x += 1;
					c.deviceCoordinateVertices[i].x *= (float)window.GetWidth() / 2.0f;
					c.deviceCoordinateVertices[i].y += 1;
					c.deviceCoordinateVertices[i].y *= (float)window.GetHeight() / 2.0f;
				}

				Vector4 viewingVector4 = Vector4(0, 0, 1, 0);
				viewingVector4 = Matrix4x4::GetModelMatrix(Vector3(1, 1, 1), camera.rotation, camera.position) * viewingVector4;
				Vector3 viewingVector = Vector3(viewingVector4.x, viewingVector4.y, viewingVector4.z);
				for (int i = 0; i < 12; i++)
				{
					//back-face culling
					Vector3 P1 = c.deviceCoordinateVertices[c.indices[i]._1];
					Vector3 P2 = c.deviceCoordinateVertices[c.indices[i]._2];
					Vector3 P3 = c.deviceCoordinateVertices[c.indices[i]._3];

					Vector3 s1 = P1 - P2;
					Vector3 s2 = P3 - P2;
					Vector3 normal = s1.Cross(s2);
					if (normal.Dot(viewingVector) < 0)continue;

					//draw
					MoveToEx(hdc, c.deviceCoordinateVertices[c.indices[i]._1].x, c.deviceCoordinateVertices[c.indices[i]._1].y, NULL);
					LineTo(hdc, c.deviceCoordinateVertices[c.indices[i]._2].x, c.deviceCoordinateVertices[c.indices[i]._2].y);

					MoveToEx(hdc, c.deviceCoordinateVertices[c.indices[i]._2].x, c.deviceCoordinateVertices[c.indices[i]._2].y, NULL);
					LineTo(hdc, c.deviceCoordinateVertices[c.indices[i]._3].x, c.deviceCoordinateVertices[c.indices[i]._3].y);

					MoveToEx(hdc, c.deviceCoordinateVertices[c.indices[i]._3].x, c.deviceCoordinateVertices[c.indices[i]._3].y, NULL);
					LineTo(hdc, c.deviceCoordinateVertices[c.indices[i]._1].x, c.deviceCoordinateVertices[c.indices[i]._1].y);
				}
				timer.Frame();
			}
		}
	}
}