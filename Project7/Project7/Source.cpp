#include <iostream>
#include "Plansza.h"
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string.h>

#define ID_PRZYCISK_1 501
#define ID_PRZYCISK_2 502
#define ID_PRZYCISK_3 503
#define ID_PRZYCISK_4 504
#define ID_PRZYCISK_5 505
#define ID_PRZYCISK_6 506
#define ID_PRZYCISK_7 507
#define ID_PRZYCISK_8 508
#define ID_PRZYCISK_9 509
#define ID_PRZYCISK_10 510
#define ID_PRZYCISK_11 511

using namespace std;
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
HWND zczytanie_x;
HWND zczytanie_y;
HWND hwnd;
HWND label_x;
HWND label_y;
HWND label_wynik;
Plansza plansza;

//int main() {
//	//srand(time(NULL));
//	//Plansza p = Plansza(7, 7);
//	//p.ustal_poczatkowe_ziarno(3, 3);
//	//p.ustal_poczatkowe_ziarno(4, 4);
//	//p.ustal_poczatkowe_ziarno(3, 4);
//	//p.ustal_poczatkowe_ziarno(4, 3);
//	system("pause");
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));
	plansza = Plansza(10, 10);
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
		CW_USEDEFAULT, CW_USEDEFAULT, 1100, 900, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Okno odmówiło przyjścia na świat!", "Ale kicha...", MB_ICONEXCLAMATION);
		return 1;
	}
	int tmp = 100;
	g_hPrzycisk1 = CreateWindowEx(0, "BUTTON", "Losuj ziarno", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU) ID_PRZYCISK_1, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk2 = CreateWindowEx(0, "BUTTON", "Równomiernie", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_2, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk3 = CreateWindowEx(0, "BUTTON", "Z promieniem", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_3, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk4 = CreateWindowEx(0, "BUTTON", "Von Neuman", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_4, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk5 = CreateWindowEx(0, "BUTTON", "Moore", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_5, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk6 = CreateWindowEx(0, "BUTTON", "Hexagonalne L", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_6, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk7 = CreateWindowEx(0, "BUTTON", "Hexagonalne P", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_7, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk8 = CreateWindowEx(0, "BUTTON", "Pentagonalne", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_8, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk9 = CreateWindowEx(0, "BUTTON", "Ciągłe losowanie", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_9, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk10 = CreateWindowEx(0, "BUTTON", "Reset", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_10, hInstance, NULL);
	tmp += 40;
	zczytanie_x = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		10, tmp, 70, 30, hwnd, NULL, hInstance, NULL);
	zczytanie_y = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
		90, tmp, 70, 30, hwnd, NULL, hInstance, NULL);
	tmp += 40;
	g_hPrzycisk11 = CreateWindowEx(0, "BUTTON", "Ustal wielkość", WS_CHILD | WS_VISIBLE,
		10, tmp, 150, 30, hwnd, (HMENU)ID_PRZYCISK_11, hInstance, NULL);

	HWND hStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 300, 50, 700, 700, hwnd, NULL, hInstance, NULL);

	label_x = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 10, 800, 40, 30, hwnd, NULL, hInstance, NULL);
	label_y = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 60, 800, 40, 30, hwnd, NULL, hInstance, NULL);
	label_wynik = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 10, 760, 90, 30, hwnd, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Komunikat, NULL, 0, 0))
	{
		TranslateMessage(&Komunikat);
		DispatchMessage(&Komunikat);
	}
	return Komunikat.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN: {
		RECT pkt_okna;
		GetWindowRect(hwnd, &pkt_okna);
		POINT pkt;
		GetCursorPos(&pkt);
		int tmp_x = pkt.x - pkt_okna.left - 11 - 300;
		int tmp_y = pkt.y - pkt_okna.top - 40 - 50;
		if (tmp_x >= 0 && tmp_x <= 699 && tmp_y >= 0 && tmp_y <= 699) {
			tmp_x /= (700. / (double)plansza.get_x());
			tmp_y /= (700. / (double)plansza.get_y());
			SetWindowText(label_x, to_string(tmp_x).c_str());
			SetWindowText(label_y, to_string(tmp_y).c_str());
			plansza.ustal_poczatkowe_ziarno(tmp_x, tmp_y);
		
		HDC hdcOkno = GetDC(hwnd);
		HBRUSH wypelnienie, wypelnienie_opakowanie;
		HPEN ramka, ramka_opakowanie;
		wypelnienie = CreateSolidBrush(plansza.tabela_kolorow.get_kolor(plansza.tabela_kolorow.get_id()));
		ramka = CreatePen(PS_SOLID, 1, plansza.tabela_kolorow.get_kolor(plansza.tabela_kolorow.get_id()));
		wypelnienie_opakowanie = (HBRUSH)SelectObject(hdcOkno, wypelnienie);
		ramka_opakowanie = (HPEN)SelectObject(hdcOkno, ramka);
		int x1 = (double)tmp_x * 700. / (double)plansza.get_x() + 300.;
		int x2 = (double)tmp_x * 700. / (double)plansza.get_x() + 700. / (double)plansza.get_x() + 300.;
		int y1 = (double)tmp_y * 700. / (double)plansza.get_y() + 50.;
		int y2 = (double)tmp_y * 700. / (double)plansza.get_y() + 700. / (double)plansza.get_y() + 50.;
		if (x1 == x2)
			x2 = x1 + 1;
		if (y2 == y1)
			y2 = y1 + 1;
		Rectangle(hdcOkno, x1, y1, x2, y2);
		SelectObject(hdcOkno, wypelnienie);
		SelectObject(hdcOkno, ramka);
		DeleteObject(wypelnienie);
		DeleteObject(ramka);
		ReleaseDC(hwnd, hdcOkno);
		}
		break;
	}

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (wParam) {
		case ID_PRZYCISK_1: {
			int tmp_x;
			int tmp_y;
			if (plansza.czy_znajduje_sie_zero()) {
				while (true) {
					tmp_x = rand() % plansza.get_x();
					tmp_y = rand() % plansza.get_y();
					if (plansza.get_tab(tmp_x, tmp_y) == 0)
						break;
				}
				plansza.ustal_poczatkowe_ziarno(tmp_x, tmp_y);
				plansza.maluj(hwnd);
				break;
			}}
		case ID_PRZYCISK_2: {
			int grupa_modulo_x = plansza.get_x() / 3;
			int grupa_modulo_y = plansza.get_y() / 3;
			for (int i = 0; i < plansza.get_y(); i++)
				for (int j = 0; j < plansza.get_x(); j++)
					if (i%grupa_modulo_x == grupa_modulo_x/2 && j%grupa_modulo_y == grupa_modulo_y/2)
						plansza.ustal_poczatkowe_ziarno(i, j);
			plansza.maluj(hwnd);
			break;
		}
		case ID_PRZYCISK_4:
			plansza.von_neuman(hwnd);
			break;
		case ID_PRZYCISK_5:
			plansza.moore(hwnd);
			break;
		case ID_PRZYCISK_10:
			plansza.reset();
			plansza.maluj(hwnd);
			break;
		case ID_PRZYCISK_11:
			plansza.reset();
			plansza.maluj(hwnd);
			DWORD dlugosc = GetWindowTextLength(zczytanie_x);
			LPSTR Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(zczytanie_x, Bufor, dlugosc + 1);
			DWORD dlugosc2 = GetWindowTextLength(zczytanie_x);
			LPSTR Bufor2 = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(zczytanie_x, Bufor2, dlugosc + 1);
			if (strlen(Bufor) == 0 && strlen(Bufor2) == 0) {
				plansza.zmien_rozmiar(10, 10);
				break;
			}
			plansza.zmien_rozmiar(atoi(Bufor),atoi(Bufor2));
			GlobalFree(Bufor);
			GlobalFree(Bufor2);
			break;
		}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}