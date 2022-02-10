#pragma once

#include <iostream>
#include <string>
#include "Biblioteka.h"

using namespace std;

class Symulacja												//obiekt stanowiacy centrum programu.
{
private:
	Biblioteka *B;											//instancja obiektu Biblioteka. W nim znajduje sie wiekszosc potrzebnych metod
	int Liczba_Kont;
	int Liczba_Filii;										//Filie reprezentuja mozliwosc wielu bibliotek wspoltworzacych system
	int numer_tury = 0;										//iteracja bedzie sie odbywala po tej zmiennej
	int dlugosc_tury = 5;									//iteracja co 5 dni
public:
	Symulacja(int input_Liczba_Kont, int input_Liczba_Filii) 
		:Liczba_Kont(input_Liczba_Kont), Liczba_Filii(input_Liczba_Filii)
	{
	this->B = new Biblioteka(Liczba_Filii, Liczba_Kont);	//generowanie kont i ksiazek
	}
	void Akcja_Gracza();									//podanie mozliwych akcji w turze
	void Aktualizuj_Stan_Wypozyczenia();					//aktualizacja czasu do oddania, naliczenie oplat
	void Tura();											//iteracja, tj naliczanie naleznosci i plyniecie czasu
	void Symuluj();											//iteracja po turach
};

void Symulacja::Akcja_Gracza()
{
	cout << "Mozliwe akcje do wykonania:" << endl;
	cout << "Komenda\t\tWykonywana akcja" << endl;
	cout << "zasoby\t\tDrukuj dane o dostepnych ksiazkach" << endl;
	cout << "konta\t\tDrukuj dane o kontach" << endl;
	cout << "zalozK\t\tZaloz konto" << endl;
	cout << "sprawdzK\tSprawdz wypozyczone ksiazki" << endl;
	//cout << "wk\t\tWyszukaj ksiazke po kodzie" << endl;
	//cout << "wn\t\tWyszukaj ksiazke po fragmencie nazwy lub nazwisku autora" << endl;
	cout << "wypk\t\tWypozycz ksiazke z filii" << endl;
	cout << "oddk\t\tOddaj ksiazke" << endl;
	cout << "przedluz\tPrzedluz wypozyczenie ksiazek" << endl;
	cout << "zaplac\t\tZaplac kare za nieoddanie ksiazek w terminie" << endl;
	cout << "e\t\tSkoncz ture" << endl;
	cout << "\n\n";

	std::string Komenda;

	do
	{
		cin >> Komenda;
		if (Komenda == "zasoby") B->Drukuj_Zasoby();
		else if (Komenda == "konta") B->Drukuj_Konta();
		else if (Komenda == "zalozK")
		{
			bool typ;
			string Nazwisko;
			cout << "Podaj liczbe typ konta, 0 dla studenta lub 1 dla pracownika uczelni" << endl;
			cin >> typ;
			cout << "Podaj Nazwisko" << endl;
			getline(cin >> ws, Nazwisko);
			B->Dodaj_Konto(typ, Nazwisko);
		}
		else if (Komenda == "sprawdzK")
		{
			cout << "Podaj numer konta" << endl;
			int input_numer;
			cin >> input_numer;
			B->Drukuj_Wypozyczenia_Konta(input_numer);
			cout << "Nalezy sie " << B->Drukuj_Naleznosc(input_numer) << " zlotych Bibliotece" << endl;
		}
		/*else if (Komenda == "wk")
		{
			cout << "Podaj ID ksiazki do wyszukania" << endl;
			int input_ID;
			cin >> input_ID;
			B->Szukaj_Ksiazki_ID(input_ID);
		}
		else if (Komenda == "wn")
		{
		}*/
		else if (Komenda == "wypk")
		{
			cout << "Podaj ID ksiazki do wypozyczenia" << endl;
			int input_ID;
			cin >> input_ID;
			cout << "Podaj numer konta osoby wypozyczajacej" << endl;
			int input_numer;
			cin >> input_numer;
			B->Wypozycz(input_ID, input_numer);
		}
		else if (Komenda == "oddk")
		{
			cout << "Podaj indeks ksiazki, ktora chcesz oddac" << endl;
			int input_ID;
			cin >> input_ID;
			B->Oddaj(input_ID);
		}
		else if (Komenda == "przedluz")
		{
			cout << "Podaj numer konta" << endl;
			int input_numer;
			cin >> input_numer;
			B->Przedluz_Ksiazki(input_numer);
		}
		else if (Komenda == "zaplac")
		{
			cout << "Podaj numer konta" << endl;
			int input_ID;
			cin >> input_ID;
			B->Oddaj_Naleznosc(input_ID);
		}
		else if (Komenda == "e") {}
		else { cout << "Blad, sprobuj ponownie" << endl; }
		cout << endl;
	} while (Komenda != "e");
}

void Symulacja::Tura()
{
	if (numer_tury == 0)
	{
		cout << "\n********************" << endl;
		cout << "Witaj w systemie biblioteki" << endl;
	}
	if (numer_tury != 0)
	{
		cout << "\n\n********************" << endl;
		cout << "Minelo " << dlugosc_tury<< " dni" << endl;

	}
	B->Aktualizuj_Stan_Wypozyczenia(dlugosc_tury);
	Akcja_Gracza();
}

void Symulacja::Symuluj()
{
	do
	{
		Tura();
		numer_tury++;
	} while (numer_tury < 1000);						//Ograniczenie czasu trwania symulacji do 1000 tur
}