#include <windows.h>
#include <string>
#include <iostream>
#include <cstdlib>

LPSTR NazwaKlasy = "Klasa Okienka";

WNDCLASSEX wc;
MSG Komunikat;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND g_hPrzycisk1;
HWND g_hPrzycisk2;
HWND g_hPrzycisk3;
HWND g_hPrzycisk4;
HWND g_hPrzycisk5;
HWND g_hPrzycisk6;
HWND g_hPrzycisk7;
HWND g_hPrzycisk8;
HWND g_hPrzycisk9;
HWND g_hPrzycisk10;
HWND g_hPrzycisk11;
HWND hText;
HWND hwnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NazwaKlasy;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NazwaKlasy, "Ziarenka", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 800, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Okno odmówi³o przyjœcia na œwiat!", "Ale kicha...", MB_ICONEXCLAMATION);
		return 1;
	}
	int tmp = 100;
	g_hPrzycisk1 = CreateWindowEx(0, "BUTTON", "Losuj ziarno", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk2 = CreateWindowEx(0, "BUTTON", "Równomiernie", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk3 = CreateWindowEx(0, "BUTTON", "Z promieniem", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk4 = CreateWindowEx(0, "BUTTON", "Von Neuman", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk2 = CreateWindowEx(0, "BUTTON", "Moore", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk2 = CreateWindowEx(0, "BUTTON", "Hexagonalne L", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk2 = CreateWindowEx(0, "BUTTON", "Hexagonalne P", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk2 = CreateWindowEx(0, "BUTTON", "Pentagonalne", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk2 = CreateWindowEx(0, "BUTTON", "Ci¹g³e losowanie", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, NULL, hInstance, NULL);

	/*hText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		50, 50, 150, 20, hwnd, NULL, hInstance, NULL);*/
	HWND hStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 300, 50, 650, 650, hwnd, NULL, hInstance, NULL);
	

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Komunikat, NULL, 0, 0))
	{
		TranslateMessage(&Komunikat);
		DispatchMessage(&Komunikat);
	}
	return Komunikat.wParam;
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		if ((HWND)lParam == g_hPrzycisk1) {/*
			DWORD dlugosc = GetWindowTextLength(hText);
			LPSTR Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(hText, Bufor, dlugosc + 1);*/
			/*LPRECT rozmiar_okna = (LPRECT)GlobalAlloc(GPTR,8);
			GetWindowRect(hwnd, rozmiar_okna);
			int x = rozmiar_okna->right;
			int y = rozmiar_okna->bottom;
			char* napis = new char[20];
			std::string napis2;
			napis2 = "Rozmiar to ";
			napis2 += std::to_string(x);
			for (int i = 0; i < napis2.length(); i++)
				napis[i] = napis2[i];
			LPSTR Bufor = (LPSTR)GlobalAlloc(GPTR, 80);
			Bufor = napis;*/
			//MessageBox(hwnd, "mam dosc", "Okienko" , MB_ICONINFORMATION);
			HDC hdcOkno;
			hdcOkno = GetDC(hwnd);
			POINT stary_punkt;
			int rand_x = (rand() % 650) + 300;
			int rand_y = (rand() % 650) + 50;
			MoveToEx(hdcOkno, rand_x, rand_y, &stary_punkt);
			LineTo(hdcOkno, rand_x + 1, rand_y + 1);
			ReleaseDC(hwnd, hdcOkno);
			break;
		}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}