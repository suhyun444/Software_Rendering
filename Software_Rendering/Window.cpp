#include "Window.h"

int Window::height = 720;
int Window::width = 1280;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;

	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(NULL, TEXT("�����Ͻðڽ��ϱ�?"), TEXT("����"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(hwnd);
			}
		}
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(HINSTANCE _hInstance, int _width, int _height, std::wstring _title)
{
	hInstance = _hInstance;
	width = _width;
	height = _height;
	title = _title;
}
bool Window::InitializeWindow()
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.lpszClassName = TEXT("Software_Rendering");
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpfnWndProc = WindowProc;

	if (RegisterClass(&wc) == false) {
		MessageBoxW(nullptr, L"RegisterClass Failed", L"Error", 0);
		exit(-1);
	}
	RECT rect = { 0,0,width,height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	hwnd = CreateWindow(wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW, 0, 0,
		width, height, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBoxW(nullptr, L"CreateWindow Failed", L"Error", 0);
		return false;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	
	return true;
}