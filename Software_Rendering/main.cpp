#include "Window.h"
#include "math.h"
#include "Cube.h"
#include "Camera.h"
#include "Time.h"
#include "BitmapBuffer.h"
#include <iostream>
#include <algorithm>
#include "ObjParser.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

const float FPS = 1.0f/144.0f;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	Window window = Window(hInstance, 720, 480, L"SoftwareRendering");
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
	Object sphere = ObjParser::LoadObject("Sphere.obj", "Brick.bmp", "BrickNormal.bmp");
	sphere.scale = Vector3(0.01f,0.01f,0.01f);
	//sphere.rotation = Vector3(0.0f,0.0f,180.0f);

	Object a = ObjParser::LoadObject("Cube.obj", "Brick.bmp", "BrickNormal.bmp");
	// sphere.scale = Vector3(0.1f,0.1f,0.1f);
	// sphere.rotation = Vector3(0.0f,0.0f,180.0f);
	a.position = Vector3(4.0f,0.0f,0.0f);
	char frameBuffer[10];

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
 				Time::Frame();
				bitmapBuffer.Clear();

				camera.Update();
				sphere.UpdateTransform(camera);
				a.UpdateTransform(camera);

				// Draw Start
				Draw::Update(camera.position);
				Draw::PrintText(hdc, 5, 5, Time::GetFrameCount(frameBuffer));
				sphere.Draw(bitmapBuffer,camera);
				a.Draw(bitmapBuffer,camera);
				//Draw End


				bitmapBuffer.Draw();
			}
		}
	}
}