#include "Window.h"
#include "math.h"
#include "Cube.h"
#include "Camera.h"
#include "Time.h"
#include "BitmapBuffer.h"
#include <iostream>
#include <algorithm>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

const float FPS = 1.0f/144.0f;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	Window window = Window(hInstance, 1280, 720, L"SoftwareRendering");
	if (window.InitializeWindow() == false)
	{
		MessageBoxW(nullptr, L"InitializeWindow Failed", L"Error", 0);
		exit(-1);
	}
	if (!Time::Initialize())return 0;

	HDC hdc = GetDC(window.GetHWND());
	BitmapBuffer bitmapBuffer = BitmapBuffer(window.GetHWND(),Window::width,Window::height);

	// 카메라 생성
	Camera camera = Camera(0.1f, 100, (float)Window::width / (float)Window::height, 70);

	//큐브 생성
	Cube cube;

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
			Time::Update();
			if (Time::GetDeltaTime() > FPS)
			{
				bitmapBuffer.Clear();
				Time::Frame();
				char frameBuffer[10];

				camera.Update();
				cube.UpdateTransform(camera);
				
				//Draw Start
				Draw::PrintText(hdc, 5, 5, Time::GetFrameCount(frameBuffer));

				Vector3 v1 = Vector3(300, 100, 0.5f), v2 = Vector3(100, 100, 0.5f), v3 = Vector3(200, 200, 0.5f);
				Draw::DrawTriangle(bitmapBuffer, v1, v2, v3);

				cube.Draw(bitmapBuffer, camera);
				//Draw End


				bitmapBuffer.Draw();
			}
		}
	}
}