#include "Window.h"
#include "math.h"
#include "Cube.h"
#include "Camera.h"
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	Window window = Window(hInstance, 1280, 720, L"SoftwareRendering");
	if (window.InitializeWindow() == false)
	{
		MessageBoxW(nullptr, L"InitializeWindow Failed", L"Error", 0);
		exit(-1);
	}
	HDC hdc = GetDC(window.GetHWND());
	float aspect = 720.0f / 1280.0f;
	Camera camera = Camera(0.1f, 100, aspect, 70);
	camera.position = Vector3(0, 0, 0);
	Cube c;
	c.scale = Vector3(0.5f, 0.5f, 0.5f);
	c.rotation = Vector3(-30, -30,0);
	c.position = Vector3(0, 0, 3);
	camera.SetViewMatrix();
	camera.SetProjectionMatrix();
	Matrix4x4 t = camera.GetProjectionMatrix() * camera.GetViewMatrix() * Matrix4x4::GetModelMatrix(c.scale, c.rotation, c.position);
	for (int i = 0; i < 8; i++)
	{
		Vector4 p = Vector4(c.vertices[i]);
		Vector4 vNdcs = t * p;
		c.vertices[i] = Vector3(vNdcs.x , vNdcs.y, vNdcs.z);
		c.vertices[i] = Vector3(vNdcs.x / vNdcs.w , vNdcs.y / vNdcs.w, vNdcs.z / vNdcs.w);
		c.vertices[i].x += 1;
		c.vertices[i].x *= window.GetWidth() / 2;
		c.vertices[i].y += 1;
		c.vertices[i].y *= window.GetHeight() / 2;
		//std::cout << vNdcs.x << " , " << vNdcs.y << " , " << vNdcs.z << " , "  << vNdcs.w << "\n";
		std::cout << c.vertices[i].x << " , " << c.vertices[i].y << " , " << c.vertices[i].z << " , "  << vNdcs.w << "\n";
	}
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			for (int i = 0; i < 12; i++)
			{
				MoveToEx(hdc, c.vertices[c.indices[i]._1].x, c.vertices[c.indices[i]._1].y, NULL);
				LineTo(hdc, c.vertices[c.indices[i]._2].x, c.vertices[c.indices[i]._2].y);

				MoveToEx(hdc, c.vertices[c.indices[i]._2].x, c.vertices[c.indices[i]._2].y, NULL);
				LineTo(hdc, c.vertices[c.indices[i]._3].x, c.vertices[c.indices[i]._3].y);

				MoveToEx(hdc, c.vertices[c.indices[i]._3].x, c.vertices[c.indices[i]._3].y, NULL);
				LineTo(hdc, c.vertices[c.indices[i]._1].x, c.vertices[c.indices[i]._1].y);

			}
		}
	}

}