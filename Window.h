#pragma once
#include <Windows.h>
#include <atlimage.h>
#include <atlstr.h>

class Window
{
protected:
	MSG msg;
	BOOL bRet;
	static LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	WNDCLASS wc;
	bool isOpen;
	
	HFONT mainFont;
	

public:
	int WindowWidth;
	int WindowHeight;
	int WindowX;
	int WindowY;
	HWND hWnd;
	HDC hDC;

	Window(int winX, int winY, int winW, int winH);
	~Window(void);

	void SaveScreen(const char* imageName);
	
	void ClearWindow();
	void StartEventSystem();
	void Show();
};

