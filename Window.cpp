#include "Window.h"


// window info
Window* CurrWin;
//-------------------


LRESULT _stdcall Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		CurrWin->isOpen = false;
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		CurrWin->isOpen = false;
		return 0;
	case WM_QUIT:
		PostQuitMessage(0);
		CurrWin->isOpen = false;
		return 0;
	case WM_SIZE:
		CurrWin->WindowWidth = LOWORD(lParam); //ширина
		CurrWin->WindowHeight = HIWORD(lParam); //высота
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	};

	return 0;
}


Window::Window(int winX, int winY, int winW, int winH)
{
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);				// yesli vyletet oshibka, to vozmojno tut
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Window";

	RegisterClass(&wc);

	hWnd = CreateWindowW(L"Window",
		L"Window",
		WS_OVERLAPPEDWINDOW,
		winX, winY, winW, winH,
		NULL, NULL, NULL, NULL);

	if (hWnd == NULL)
	{
		throw WSASYSCALLFAILURE;
		return;
	}

	this->WindowX = winX;
	this->WindowY = winY;
	this->WindowWidth = winW;
	this->WindowHeight = winH;
	CurrWin = this;
	this->isOpen = false;

	mainFont = CreateFont(15, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Courier New");
	
	this->hDC = GetDC(hWnd);
	if (this->hDC == NULL)
		throw WSASYSCALLFAILURE;

	return;
}


Window::~Window(void)
{
}

void Window::Show()
{
	isOpen = true;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

void Window::ClearWindow()
{
	RECT rect;
	GetClientRect(this->hWnd, &rect);
	FillRect(this->hDC, &rect, (HBRUSH)(6));
	return;
}


void Window::StartEventSystem()
{
	while ((bRet = GetMessage(&msg, hWnd, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			//printf("%ld\n", GetLastError());
			throw GetLastError();
			return;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (!this->isOpen)
		{
			break;
		}
	}
	return;
}