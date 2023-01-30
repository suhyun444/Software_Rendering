#include "Window.h"
#include "math.h"
#include "Cube.h"
#include "Camera.h"
#include "Time.h"
#include <iostream>
#include <algorithm>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

const float FPS = 1/60;
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
	Camera camera = Camera(0.1f, 100, (float)Window::width / (float)Window::height, 70);

	//큐브 생성
	Cube cube;
	cube.scale = Vector3(1, 1, 1);
	cube.rotation = Vector3(-30, -30, 0);
	cube.position = Vector3(0, 0, 0);
	
	if (!Time::Initialize())return 0;

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
			if (Time::GetDeltaTime() > FPS)
			{
				Time::Frame();
				BitBlt(hdc, 0, 0, Window::width, Window::height, 0, 0, 0, WHITENESS);
				camera.Update();
				cube.UpdateTransform(camera);
				cube.Draw(hdc,camera);
			}
		}
	}
}