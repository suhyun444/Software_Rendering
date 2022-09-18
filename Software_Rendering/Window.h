#pragma once
#include <Windows.h>
#include <string>

class Window
{
private:
	int width;
	int height;
	std::wstring title;
	HWND hwnd;
	HINSTANCE hInstance;

public:
	Window(HINSTANCE _hInstance,int _width,int _height,std::wstring _title);
	bool InitializeWindow();
	HWND GetHWND() { return hwnd;  }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	
};