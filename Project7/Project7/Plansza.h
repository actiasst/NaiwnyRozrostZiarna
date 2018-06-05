#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

class Tabela_kolorow {
	int kolor[100000];
	int id;
public:
	Tabela_kolorow();
	void dodaj_kolor();
	int losuj_kolor();
	int get_id();
	void set_id(int);
	int get_kolor(int);
	void set_kolor(int,int);
};

class Plansza {
	int x;
	int y;
	int** tab;
public:
	bool czy_narysowane[700][700];
	Tabela_kolorow tabela_kolorow;
	Plansza();
	Plansza(int x, int y);
	void wyswietl();
	void ustal_poczatkowe_ziarno(int x, int y);
	void moore(HWND);
	void von_neuman(HWND);
	int** utworz_tablice_tmp();
	void usun_tablice_tmp(int**);
	int* utworz_tab_wynik();
	void zeruj_tab_wynik(int*);
	void usun_tab_wynik(int*);
	int znajdz_maksimum(int*);
	void zamien(int**);
	void set_x(int);
	void set_y(int);
	int get_x();
	int get_y();
	int get_tab(int,int);
	void reset();
	void zmien_rozmiar(int x, int y);
	bool czy_znajduje_sie_zero();
	void maluj(HWND);
	void maluj2(HWND);
};
