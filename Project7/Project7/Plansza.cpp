#include "Plansza.h"

Plansza::Plansza(){}

Plansza::Plansza(int x, int y) {
	this->x = x;
	this->y = y;

	tab = new int*[y];
	for (int i = 0; i < y; i++)
		tab[i] = new int[x];

	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			tab[i][j] = 0;


	for (int i = 0; i < 700; i++) {
		for (int j = 0; j < 700; j++)
			czy_narysowane[i][j] = false;
	}
}

void Plansza::wyswietl() {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
			if (tab[i][j] >= 0)
				std::cout << tab[i][j];
			else
				std::cout << " ";
		std::cout << std::endl;
	}
}

void Plansza::set_x(int x) {
	this->x = x;
}

void Plansza::set_y(int y) {
	this->x = x;
}

int Plansza::get_x() {
	return x;
}

int Plansza::get_y() {
	return y;
}

int Plansza::get_tab(int x, int y) {
	return tab[y][x];
}

void Plansza::ustal_poczatkowe_ziarno(int x, int y) {
	tabela_kolorow.dodaj_kolor();
	tab[y][x] = tabela_kolorow.get_id();
}

Tabela_kolorow::Tabela_kolorow() {
	id = 0;
	kolor[0] = 0xF0F0F0;
}

void Tabela_kolorow::dodaj_kolor() {
	id++;
	this->kolor[id] = losuj_kolor();
}

int Tabela_kolorow::losuj_kolor() {
	int tmp = rand() % 256;
	int tmp2 = rand() % 256;
	int tmp3 = rand() % 256;
	return tmp * 65536 + tmp2 * 256 + tmp3;
}

int Tabela_kolorow::get_id() {
	return id;
}

void Tabela_kolorow::set_id(int id) {
	this->id = id;
}

int Tabela_kolorow::get_kolor(int tmp) {
	return kolor[tmp];
}

void Tabela_kolorow::set_kolor(int id, int kolor) {
	this->kolor[id] = kolor;
}

int** Plansza::utworz_tablice_tmp() {
	int** tmp = new int*[y];
	for (int i = 0; i < y; i++)
		tmp[i] = new int[x];
	return tmp;
}

void Plansza::usun_tablice_tmp(int** tmp) {
	for (int i = 0; i < y; i++)
		delete[] tmp[i];
	delete[] tmp;
}

void Plansza::zeruj_tab_wynik(int* tmp) {
	for (int i = 0; i < tabela_kolorow.get_id() + 1; i++)
		tmp[i] = 0;
}

void Plansza::usun_tab_wynik(int* tmp) {
	delete[] tmp;
}

int* Plansza::utworz_tab_wynik() {
	int* tmp = new int[tabela_kolorow.get_id()+1];
	for (int i = 0; i < tabela_kolorow.get_id()+1; i++)
		tmp[i] = 0;
	return tmp;
}

int Plansza::znajdz_maksimum(int* tmp) {
	int maks = 0;
	int wynik = 0;
	for(int i = 1; i < tabela_kolorow.get_id() + 1; i++)
		if (tmp[i] > maks) {
			maks = tmp[i];
			wynik = i;
		}
	return wynik;
}

void Plansza::zamien(int** tmp) {
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			tab[i][j] = tmp[i][j];
}

void Plansza::reset() {
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			tab[i][j] = 0;

	for (int i = 0; i < 700; i++)
		for (int j = 0; j < 700; j++)
			czy_narysowane[i][j] = false;

	tabela_kolorow.set_id(0);
}

void Plansza::zmien_rozmiar(int tmp_x, int tmp_y) {
	for (int i = 0; i < this->y; i++)
		delete[] tab[i];
	delete[] tab;

	this->x = tmp_x;
	this->y = tmp_y;

	tab = new int*[this->y];
	for (int i = 0; i < this->y; i++)
		tab[i] = new int[this->x];

	for (int i = 0; i < this->y; i++)
		for (int j = 0; j < this->x; j++)
			tab[i][j] = 0;

	tabela_kolorow.set_id(0);
}

bool Plansza::czy_znajduje_sie_zero() {
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			if (tab[i][j] == 0)
				return true;
	return 
		false;
}

void Plansza::maluj(HWND hwnd) {
	int x1;
	int x2;
	int y1;
	int y2;
	HDC hdcOkno = GetDC(hwnd);
	HBRUSH *wypelnienie, wypelnienie_opakowanie;
	wypelnienie = new HBRUSH[tabela_kolorow.get_id() + 1];
	HPEN *ramka, ramka_opakowanie;
	ramka = new HPEN[tabela_kolorow.get_id() + 1];
	for (int i = 0; i < tabela_kolorow.get_id() + 1; i++) {
		wypelnienie[i] = CreateSolidBrush(tabela_kolorow.get_kolor(i));
		ramka[i] = CreatePen(PS_SOLID, 1, tabela_kolorow.get_kolor(i));
	}
	for(int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			wypelnienie_opakowanie = (HBRUSH)SelectObject(hdcOkno, wypelnienie[tab[i][j]]);
			ramka_opakowanie = (HPEN)SelectObject(hdcOkno, ramka[tab[i][j]]);
			x1 = (double)j * 700. / (double)get_x() + 300.;
			x2 = (double)j * 700. / (double)get_x() + 700. / (double)get_x() + 300.;
			y1 = (double)i * 700. / (double)get_y() + 50.;
			y2 = (double)i * 700. / (double)get_y() + 700. / (double)get_y() + 50.;
			if (x1 == x2)
				x2 = x1 + 1;
			if (y2 == y1)
				y2 = y1 + 1;
			Rectangle(hdcOkno, x1, y1, x2, y2);
		}

	DeleteObject(wypelnienie);
	DeleteObject(ramka);
	ReleaseDC(hwnd, hdcOkno);
	delete[] ramka;
	delete[] wypelnienie;
}

void Plansza::maluj2(HWND hwnd) {
	HDC hdcOkno = GetDC(hwnd);
	HBRUSH *wypelnienie, wypelnienie_opakowanie;
	wypelnienie = new HBRUSH[tabela_kolorow.get_id() + 1];
	HPEN *ramka, ramka_opakowanie;
	ramka = new HPEN[tabela_kolorow.get_id() + 1];
	for (int i = 0; i < tabela_kolorow.get_id() + 1; i++) {
		wypelnienie[i] = CreateSolidBrush(tabela_kolorow.get_kolor(i));
		ramka[i] = CreatePen(PS_SOLID, 1, tabela_kolorow.get_kolor(i));
	}
	for (int i = 0; i < 700; i++)
		for (int j = 0; j < 700; j++) {
			int tmp_x = i / (700. / x);
			int tmp_y = j / (700. / y);
			int kolor = tabela_kolorow.get_kolor(tab[tmp_y][tmp_x]);
			if (kolor != 0xF0F0F0 && !czy_narysowane[i][j]) {
				SetPixel(hdcOkno, i + 300, j + 50, kolor);
				czy_narysowane[i][j] = true;
			}
		}
	DeleteObject(wypelnienie);
	DeleteObject(ramka);
	ReleaseDC(hwnd, hdcOkno);
	delete[] ramka;
	delete[] wypelnienie;
}

void Plansza::moore(HWND hwnd) {
	if (tabela_kolorow.get_id() != 0) {

		int** tmp = utworz_tablice_tmp();
		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
				tmp[i][j] = tab[i][j];
		int* tab_wynik = utworz_tab_wynik();

		while (czy_znajduje_sie_zero()) {
			zeruj_tab_wynik(tab_wynik);

			if (tab[0][0] == 0) {
				tab_wynik[tab[0][1]]++;
				tab_wynik[tab[1][0]]++;
				tab_wynik[tab[1][1]]++;
				tmp[0][0] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			if (tab[y - 1][x - 1] == 0) {
				tab_wynik[tab[y - 1][x - 2]]++;
				tab_wynik[tab[y - 2][x - 2]]++;
				tab_wynik[tab[y - 2][x - 1]]++;
				tmp[y - 1][x - 1] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			if (tab[0][x - 1] == 0) {
				tab_wynik[tab[0][x - 2]]++;
				tab_wynik[tab[1][x - 2]]++;
				tab_wynik[tab[1][x - 1]]++;
				tmp[0][x - 1] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			if (tab[y - 1][0] == 0) {
				tab_wynik[tab[y - 2][0]]++;
				tab_wynik[tab[y - 2][1]]++;
				tab_wynik[tab[y - 1][0]]++;
				tmp[y - 1][0] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			for (int i = 1; i < x - 1; i++) {
				if (tab[0][i] == 0) {
					tab_wynik[tab[1][i - 1]]++;
					tab_wynik[tab[1][i]]++;
					tab_wynik[tab[1][i + 1]]++;
					tab_wynik[tab[0][i - 1]]++;
					tab_wynik[tab[0][i + 1]]++;
					tmp[0][i] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < x - 1; i++) {
				if (tab[y - 1][i] == 0) {
					tab_wynik[tab[y - 2][i - 1]]++;
					tab_wynik[tab[y - 2][i]]++;
					tab_wynik[tab[y - 2][i + 1]]++;
					tab_wynik[tab[y - 1][i - 1]]++;
					tab_wynik[tab[y - 1][i + 1]]++;
					tmp[y - 1][i] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < y - 1; i++) {
				if (tab[i][0] == 0) {
					tab_wynik[tab[i - 1][1]]++;
					tab_wynik[tab[i][1]]++;
					tab_wynik[tab[i + 1][1]]++;
					tab_wynik[tab[i - 1][0]]++;
					tab_wynik[tab[i + 1][0]]++;
					tmp[i][0] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < y - 1; i++) {
				if (tab[i][x - 1] == 0) {
					tab_wynik[tab[i - 1][x - 2]]++;
					tab_wynik[tab[i][x - 2]]++;
					tab_wynik[tab[i + 1][x - 2]]++;
					tab_wynik[tab[i - 1][x - 1]]++;
					tab_wynik[tab[i + 1][x - 1]]++;
					tmp[i][x - 1] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < y - 1; i++)
				for (int j = 1; j < x - 1; j++) {
					if (tab[i][j] == 0) {
						tab_wynik[tab[i - 1][j - 1]]++;
						tab_wynik[tab[i - 1][j]]++;
						tab_wynik[tab[i - 1][j + 1]]++;
						tab_wynik[tab[i][j - 1]]++;
						tab_wynik[tab[i][j + 1]]++;
						tab_wynik[tab[i + 1][j - 1]]++;
						tab_wynik[tab[i + 1][j]]++;
						tab_wynik[tab[i + 1][j + 1]]++;
						//std::cout << tab_wynik[0] << " " << tab_wynik[1] << " " << tab_wynik[2] <<  std::endl;
						tmp[i][j] = znajdz_maksimum(tab_wynik);
						zeruj_tab_wynik(tab_wynik);
					}
				}
			zamien(tmp);
			if (x < 400)
				maluj(hwnd);
			else
				maluj2(hwnd);
		}
		usun_tablice_tmp(tmp);
		usun_tab_wynik(tab_wynik);
	}
}

void Plansza::von_neuman(HWND hwnd) {
	if (tabela_kolorow.get_id() != 0) {

		int** tmp = utworz_tablice_tmp();
		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
				tmp[i][j] = tab[i][j];
		int* tab_wynik = utworz_tab_wynik();

		while (czy_znajduje_sie_zero()) {
			zeruj_tab_wynik(tab_wynik);

			if (tab[0][0] == 0) {
				tab_wynik[tab[0][1]]++;
				tab_wynik[tab[1][0]]++;
				tmp[0][0] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			if (tab[y - 1][x - 1] == 0) {
				tab_wynik[tab[y - 1][x - 2]]++;
				tab_wynik[tab[y - 2][x - 1]]++;
				tmp[y - 1][x - 1] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			if (tab[0][x - 1] == 0) {
				tab_wynik[tab[0][x - 2]]++;
				tab_wynik[tab[1][x - 1]]++;
				tmp[0][x - 1] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			if (tab[y - 1][0] == 0) {
				tab_wynik[tab[y - 2][0]]++;
				tab_wynik[tab[y - 1][1]]++;
				tmp[y - 1][0] = znajdz_maksimum(tab_wynik);
				zeruj_tab_wynik(tab_wynik);
			}
			for (int i = 1; i < x - 1; i++) {
				if (tab[0][i] == 0) {
					tab_wynik[tab[1][i]]++;
					tab_wynik[tab[0][i - 1]]++;
					tab_wynik[tab[0][i + 1]]++;
					tmp[0][i] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < x - 1; i++) {
				if (tab[y - 1][i] == 0) {
					tab_wynik[tab[y - 2][i]]++;
					tab_wynik[tab[y - 1][i - 1]]++;
					tab_wynik[tab[y - 1][i + 1]]++;
					tmp[y - 1][i] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < y - 1; i++) {
				if (tab[i][0] == 0) {
					tab_wynik[tab[i][1]]++;
					tab_wynik[tab[i - 1][0]]++;
					tab_wynik[tab[i + 1][0]]++;
					tmp[i][0] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < y - 1; i++) {
				if (tab[i][x - 1] == 0) {
					tab_wynik[tab[i][x - 2]]++;
					tab_wynik[tab[i - 1][x - 1]]++;
					tab_wynik[tab[i + 1][x - 1]]++;
					tmp[i][x - 1] = znajdz_maksimum(tab_wynik);
					zeruj_tab_wynik(tab_wynik);
				}
			}
			for (int i = 1; i < y - 1; i++)
				for (int j = 1; j < x - 1; j++) {
					if (tab[i][j] == 0) {
						tab_wynik[tab[i - 1][j]]++;
						tab_wynik[tab[i][j - 1]]++;
						tab_wynik[tab[i][j + 1]]++;
						tab_wynik[tab[i + 1][j]]++;
						//std::cout << tab_wynik[0] << " " << tab_wynik[1] << " " << tab_wynik[2] <<  std::endl;
						tmp[i][j] = znajdz_maksimum(tab_wynik);
						zeruj_tab_wynik(tab_wynik);
					}
				}
			zamien(tmp);
			if (x < 400)
				maluj(hwnd);
			else
				maluj2(hwnd);
			Sleep(200);
		}
		usun_tablice_tmp(tmp);
		usun_tab_wynik(tab_wynik);
	}
}