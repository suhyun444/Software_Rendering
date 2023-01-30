#pragma once
#include <Windows.h>
#include <string>

class Window
{
private:
	std::wstring title;
	HWND hwnd;
	HINSTANCE hInstance;

public:
	static int width;
	static int height;
	Window(HINSTANCE _hInstance,int _width,int _height,std::wstring _title);
	bool InitializeWindow();
	HWND GetHWND() { return hwnd;  }
};
