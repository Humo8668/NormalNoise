#pragma once
#include <Windows.h>

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

	//int DrawGraph(float (F)(float), float ScaleX, float ScaleY, COLORREF);

	//void writeString(int x, int y, char* str);
	//void writeString(int x, int y, double num);
	
	void ClearWindow();
	void StartEventSystem();
	void Show();
};

