﻿#include "Window.h"
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
	Object cube = ObjParser::LoadObject("Cube.obj");
	cube.position = Vector3(-10,0,0);
	//cube.rotation += Vector3(-30,0,0);
	Object sphere = ObjParser::LoadObject("Sphere.obj");
	sphere.scale = Vector3(0.1f,0.1f,0.1f);
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

				//cube.rotation += Vector3(-30,60,0) * Time::GetDeltaTime();
	
				camera.Update();
				sphere.UpdateTransform(camera);
				cube.UpdateTransform(camera);

				//Draw Start
				Draw::Update(camera.position);
				Draw::PrintText(hdc, 5, 5, Time::GetFrameCount(frameBuffer));
				sphere.Draw(bitmapBuffer,camera);
				cube.Draw(bitmapBuffer, camera);
				//Draw End


				bitmapBuffer.Draw();
			}
		}
	}
}