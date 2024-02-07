#include <Windows.h>
#include <tchar.h>
#include <string>

#define SUBMIT (100)
#define TEXTBOX (100)

HINSTANCE g_instance;

void SetBackGroundImage(HDC& hdc, HBITMAP hBgImage) {
	BITMAP          bitmap;
	HDC             hdcMem;
	HGDIOBJ         oldBitmap;

	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hBgImage);

	GetObject(hBgImage, sizeof(bitmap), &bitmap);
	BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
}

LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wide_param, LPARAM long_param);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd, int cmd_show)
{
	g_instance = instance;
	HFONT hNewFont = CreateFont(24, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");

	WNDCLASSEX window_class;

	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc = WndProc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = instance;
	window_class.hIcon = LoadIcon(window_class.hInstance, IDI_APPLICATION);
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	window_class.lpszMenuName = NULL;
	window_class.lpszClassName = "window_class";
	window_class.hIconSm = LoadIcon(window_class.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&window_class))
	{
		MessageBoxA(NULL, "RegisterClassEx Failed", "2pacalypse", MB_OK);
		return 1;
	}

	HWND window = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "window_class", "2pacalypse", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX) , CW_USEDEFAULT, CW_USEDEFAULT, 1200, 676, NULL, NULL, instance, NULL);

	if (!window)
	{
		MessageBoxA(NULL, "CreateWindowEx Failed", "2pacalypse", MB_OK);
		return 1;
	}

	HWND text_edit = CreateWindow("Edit", "punk ass niggaz name", (WS_CHILD | WS_VISIBLE | WS_BORDER), 5, 40, 300, 30, window, (HMENU)TEXTBOX, NULL, NULL);
	SendMessage(text_edit, WM_SETFONT, (WPARAM)hNewFont, 0);

	if (!text_edit)
	{
		MessageBoxA(NULL, "CreateWindow Failed", "2pacalypse", MB_OK);
		return 1;
	}

	HWND submit = CreateWindow("BUTTON", "Drive by his ass", (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT), 5, 80, 160, 30, window, (HMENU)SUBMIT, (HINSTANCE)GetWindowLongPtr(window, GWLP_HINSTANCE), NULL);
	SendMessage(submit, WM_SETFONT, (WPARAM)hNewFont, 0);

	if (!submit)
	{
		MessageBoxA(NULL, "CreateWindow Failed", "2pacalypse", MB_OK);
		return 1;
	}

	ShowWindow(window, cmd_show);
	UpdateWindow(window);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND window, UINT message, WPARAM wide_param, LPARAM long_param)
{
	static HBITMAP hBgImage = NULL;

	switch (message)
	{
	case WM_CREATE:
		hBgImage = (HBITMAP)LoadImage(g_instance, "global8000.bmp", IMAGE_BITMAP, 1200, 676, LR_LOADFROMFILE);

		if (hBgImage == NULL)
			MessageBoxA(NULL, "LoadImage Failed", "2pacalypse", MB_OK);

		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		HFONT hfont;
		HFONT oldfont;

		hdc = BeginPaint(window, &ps);
		hfont = CreateFont(24, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Comic Sans MS");
		oldfont = (HFONT)SelectObject(hdc, hfont);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));

		SetBackGroundImage(hdc, hBgImage);

		TextOut(hdc, 5, 5, "2pac here, who you wanna dox nigga?", _tcslen("2pac here, who you wanna dox nigga?"));

		SelectObject(hdc, oldfont);
		DeleteObject(hfont);
		EndPaint(window, &ps);
		return 0;
	case WM_COMMAND:
		switch (wide_param)
		{
		case SUBMIT:
			int bufSize = 1024;
			LPTSTR szText = new TCHAR[bufSize];
			GetDlgItemText(window, TEXTBOX, szText, bufSize);
			std::string myString = szText;
			delete[] szText;

			if (myString == "punk ass niggaz name")
			{
				MessageBoxA(NULL, "NUH UH", "2pacalypse", MB_OK);
				break;
			}

			std::string result = "User: " + myString + "\nLocation: Homo Island\nRace: Nigger\nSexual Orientation: Gay As Shit\nWeight: 242 KG\nHeight: 142 CM\nInternet Service Provider: Fag Internet Services (FIS)\nIP Address: 192.168.42.112\nE-Mail Address: ilovebuttsex@homomail.gay";
			std::string result_1 = result + "\n\nPress OK To Copy To Clipboard";

			if (MessageBoxA(NULL, result_1.c_str(), "2pacalypse", MB_OK))
			{
				HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, result.length());
				if (hMem)
				{
					memcpy(GlobalLock(hMem), result.c_str(), result.length());
					GlobalUnlock(hMem);
					OpenClipboard(0);
					EmptyClipboard();
					SetClipboardData(CF_TEXT, hMem);
					CloseClipboard();
				}
			}

			break;
		}
		break;
	case WM_DESTROY:
		if (hBgImage != NULL)
			DeleteObject(hBgImage);

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window, message, wide_param, long_param);
		break;
	}

	return 0;
}
