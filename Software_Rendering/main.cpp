#include "Window.h"
#include "math.h"
#include "Cube.h"
#include "Camera.h"
#include "Time.h"
#include <iostream>
#include <algorithm>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

const float FPS = 1.0f/60.0f;
void DoubleBufferingStart(HDC *hdc, HDC* memDC, HBITMAP *hBit, HBITMAP *oldBit,int x,int y)
{
	*memDC = CreateCompatibleDC(*hdc);
	*hBit = CreateCompatibleBitmap(*hdc,x,y);
	*oldBit = (HBITMAP)SelectObject(*memDC,*hBit);
}
void DoubleBufferingEnd(HDC *memDC,HBITMAP *hBit, HBITMAP *oldBit)
{
	SelectObject(*memDC,*oldBit);
	DeleteDC(*memDC);
	DeleteObject(*hBit);
}
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
	HDC memDC;
	HBITMAP hBit, oldBit;
	RECT rect = {0, 0, Window::width, Window::height};

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
				DoubleBufferingStart(&hdc,&memDC,&hBit,&oldBit,rect.right,rect.bottom);
				Time::Frame();

				camera.Update();
				cube.UpdateTransform(camera);
				
				//Draw Start
				FillRect(memDC,&rect,(HBRUSH)COLOR_WINDOWFRAME);
				cube.Draw(memDC, camera);
				//Draw End

				BitBlt(hdc, 0, 0, Window::width,Window::height, memDC, 0, 0, SRCCOPY);

				DoubleBufferingEnd(&memDC,&hBit,&oldBit);
			}
		}
	}
}