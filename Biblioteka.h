#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iterator>
#include "RandomGenerator.h"
#include "Konta.h"

using namespace std;

class Ksiazka
{
private:
	string Nazwa;
	int ID;
	int Filia_ID;								//Filie reprezentuja mozliwosc wielu bibliotek wspoltworzacych system
	bool typ_konta;								//0 - student, 1 - pracownik uczelni
	bool stan_wypozyczenia;						//0 - niewypozyczone, 1 - wypozyczone
	int czas_do_oddania;						//termin, po ktorym zacznie byc naliczana kara
	int ID_Konta_Wypozyczajacego;				//informacja, kto ma w tym momencie ksiazke. Gdy jest to biblioteka, ma wartosc NULL
public:
	Ksiazka(string input_Nazwa, int input_ID, int input_Filia_ID, bool input_typ_konta)
		:Nazwa(input_Nazwa), ID(input_ID), Filia_ID(input_Filia_ID), typ_konta(input_typ_konta), stan_wypozyczenia(0), czas_do_oddania(0), ID_Konta_Wypozyczajacego(0) {}

	const bool Get_stan_wypozyczenia() const { return stan_wypozyczenia; }
	void Set_stan_wypozyczenia(bool x) { stan_wypozyczenia = x; }
	const int Get_czas_do_oddania() const { return czas_do_oddania; }
	void Set_czas_do_oddania(int t) { czas_do_oddania = t; }
	void Set_ID_Konta_Wypozyczajacego(int input_ID) { ID_Konta_Wypozyczajacego = input_ID; }
	const int Get_ID_Konta_Wypozyczajacego() const { return ID_Konta_Wypozyczajacego; }
	const int GetID() const { return ID; }

	void Drukuj()
	{
		cout << Filia_ID << "\t\t" << Nazwa << "\t" << ID << "\t" << stan_wypozyczenia << "\t\t" << czas_do_oddania << "\t\t";
		if (stan_wypozyczenia == 1)
			cout << ID_Konta_Wypozyczajacego << endl;
		else
			cout << "niewyp" << endl;			//niewypozyczone
	}
};

class Biblioteka
{
private:
	vector<unique_ptr<Konto>> ListaKont;		//postac unique_ptr z powodu dziedziczenia wewnatrz obiektu Konto
	vector <Ksiazka> Zasoby;
public:
	Biblioteka() {}
	Biblioteka(int input_Liczba_Filii, int input_Liczba_Kont) { Inicjalizacja_Biblioteki(input_Liczba_Kont, input_Liczba_Filii); }

	void Inicjalizacja_Biblioteki(int N_Kont, int N_Filii);	//generuje wektor losowych ksiazek i wektor losowych kont
	void Dodaj_Konto(bool typ, string Nazwisko);			//mozliwosc generowania wlasnego konta
	void Drukuj_Zasoby();									//drukowanie wektora ksiazek ze spisu biblioteki
	void Drukuj_Konta();									//drukowanie wektora kont ze spisu biblioteki
	void Drukuj_Wypozyczenia_Konta(int Numer_Konta)		//drukuje instancje wypozyczonych ksiazek konta numer_
		{ for_each(ListaKont[Numer_Konta]->Wypozyczone.begin(), ListaKont[Numer_Konta]->Wypozyczone.end(), [](Ksiazka k) {k.Drukuj(); });}

	void Wypozycz(int input_ID_ksiazki, int Numer_Konta);	//wypozycza ksiazke numer_ koncie o numerze_
	void Oddaj(int input_ID_ksiazki);						//zwraca ksiazke o indeksie_. Nie ma potrzeby podawac danych konta.
	void Oddaj_Naleznosc(int input_ID_konta);				//zwraca pelna kwote kary za zaleganie z oddawaniem ksiazek
	void Przedluz_Ksiazki(int input_ID_konta);				//resetuje czas na oddanie ksiazek
	void Aktualizuj_Stan_Wypozyczenia(int dlugosc_tury);	//wykonuje akcje potrzebne do iteracji po turach, tj naliczenie kar, zmiana terminu oddania ksiazek
	const int Drukuj_Naleznosc(int input_Numer_Konta) const { return ListaKont[input_Numer_Konta]->Get_Naleznosc(); }

	const int Get_Liczba_Ksiazek()const { return Zasoby.size(); }

	static const int Naleznosc = 1;							//20 groszy za dzien za ksiazke
};

void Biblioteka::Inicjalizacja_Biblioteki(int N_Kont, int N_Filii)
{
	int Liczba_Studentow = 0;
	int Liczba_Pracownikow = 0;
	int Numer_ksiazki = 0;
	for (int i = 0; i < N_Kont; i++)
	{
		if (Random_Account_Type() == 0)
		{
			ListaKont.emplace_back(new Student(Random_Name(), 100 + Liczba_Studentow));			//Studenci zajmuja indeksy 100-200
			Liczba_Studentow++;
		}
		else
		{
			ListaKont.emplace_back(new Pracownik(Random_Name(), 200 + Liczba_Pracownikow));		//Pracownicu zajmuja indeksy 200-300
			Liczba_Pracownikow++;
		}
	}
	for (int i = 0; i < N_Filii; i++)
	{
		for (int j = 0; j < Random_Book_Number(); j++)											//kazda filia posiada losowa ilosc ksiazek
		{
			Zasoby.emplace_back(Random_Book_Name(), Numer_ksiazki, i, Random_Privileges());
			Numer_ksiazki++;
		}
	}
}

void Biblioteka::Dodaj_Konto(bool typ, string Nazwisko)
{
	int Liczba_Pracownikow = count_if(ListaKont.begin(), ListaKont.end(), [](unique_ptr<Konto>& k) {return k->Get_ID() >= 200; });	//zlicza konta studenckie
	int Liczba_Studentow = count_if(ListaKont.begin(), ListaKont.end(), [](unique_ptr<Konto>& k) {return k->Get_ID() < 200; });		//zlicza konta pracownicze
	if (typ == 0)
	{
		ListaKont.emplace_back(new Student(Nazwisko, 100 + Liczba_Studentow));
	}
	else
	{
		ListaKont.emplace_back(new Pracownik(Nazwisko, 200 + Liczba_Pracownikow));
	}
}

void Biblioteka::Drukuj_Zasoby()
{
	cout << "Filia_ID" << "\t" << "Nazwa" << "\t\t\t\t\t\t\t" << "ID" << "\t" << "stan_wyp." << "\t" << "czas_do_oddania" << "\t" << "ID konta" << endl;
	for_each(Zasoby.begin(), Zasoby.end(), [](Ksiazka k) {k.Drukuj(); });
}

void Biblioteka::Drukuj_Konta()
{
	cout << "Numer na liscie" << "\t" << "Imie" << "\t" << "Nazwisko" << "\t" << "ID" << "\t" << "Typ" << endl;
	//for_each(Zasoby.begin(), Zasoby.end(), [](Ksiazka k) {k.Drukuj(); });		//nie, bo potrzebna jest numeracja po i
	for (int i = 0; i < ListaKont.size(); ++i) 
	{ 
		cout << i << "\t\t";
		ListaKont[i]->Drukuj(); 
	}
}

void Biblioteka::Wypozycz(int input_ID_ksiazki, int Numer_Konta)
{
	if (Zasoby[input_ID_ksiazki].Get_stan_wypozyczenia() == 1)
		cout << "Przykro nam, ale ksiazka jest juz wypozyczona" << endl;
	else
	{
		Zasoby[input_ID_ksiazki].Set_stan_wypozyczenia(1);
		Zasoby[input_ID_ksiazki].Set_ID_Konta_Wypozyczajacego(Numer_Konta);
		if(ListaKont[Numer_Konta]->Get_przywileje()==0)
			Zasoby[input_ID_ksiazki].Set_czas_do_oddania(30);
		else
			Zasoby[input_ID_ksiazki].Set_czas_do_oddania(90);
		ListaKont[Numer_Konta]->Wypozyczone.emplace_back(Zasoby[input_ID_ksiazki]);
	}
}

void Biblioteka::Oddaj(int input_ID_ksiazki)
{
	int ID_konta = Zasoby[input_ID_ksiazki].Get_ID_Konta_Wypozyczajacego();
	auto id = find_if(ListaKont[ID_konta]->Wypozyczone.begin(), ListaKont[ID_konta]->Wypozyczone.end(), [&](Ksiazka k) {return k.GetID() == input_ID_ksiazki; });
	int index = distance(ListaKont[ID_konta]->Wypozyczone.begin(), id);
	ListaKont[ID_konta]->Wypozyczone.erase(ListaKont[ID_konta]->Wypozyczone.begin()+index);			//usuwanie instancji z listy ksiazek wewnatrz konta

	Zasoby[input_ID_ksiazki].Set_stan_wypozyczenia(0);												//reset wlasciwosci ksiazki w spisie biblioteki
	Zasoby[input_ID_ksiazki].Set_ID_Konta_Wypozyczajacego(NULL);									//reset wlasciwosci ksiazki w spisie biblioteki
	Zasoby[input_ID_ksiazki].Set_czas_do_oddania(0);												//reset wlasciwosci ksiazki w spisie biblioteki
}

void Biblioteka::Oddaj_Naleznosc(int input_ID_konta)
{
	cout << "Zaplacono " << ListaKont[input_ID_konta]->Get_Naleznosc() << endl;
	ListaKont[input_ID_konta]->Set_Naleznosc(0);
}

void Biblioteka::Przedluz_Ksiazki(int input_ID_konta)
{
	for (int i = 0; i < ListaKont[input_ID_konta]->Wypozyczone.size(); i++)
	{
		if (ListaKont[input_ID_konta]->Get_przywileje() == 0)
			ListaKont[input_ID_konta]->Wypozyczone[i].Set_czas_do_oddania(30);
		else
			ListaKont[input_ID_konta]->Wypozyczone[i].Set_czas_do_oddania(90);
	}
}

void Biblioteka::Aktualizuj_Stan_Wypozyczenia(int dlugosc_tury)
{
	for (int i = 0; i < Zasoby.size(); i++)
		if (Zasoby[i].Get_stan_wypozyczenia() == 1 && Zasoby[i].Get_czas_do_oddania() >= 5)
			Zasoby[i].Set_czas_do_oddania(Zasoby[i].Get_czas_do_oddania() - dlugosc_tury);
	for (int i = 0; i < ListaKont.size(); i++)
		for (int j = 0; j < ListaKont[i]->Wypozyczone.size(); j++)
		{
			if (ListaKont[i]->Wypozyczone[j].Get_czas_do_oddania() >= 5)
				ListaKont[i]->Wypozyczone[j].Set_czas_do_oddania(ListaKont[i]->Wypozyczone[j].Get_czas_do_oddania() - dlugosc_tury);
			else
				ListaKont[i]->Set_Naleznosc(ListaKont[i]->Get_Naleznosc()+Naleznosc);
		}
}

/*void Biblioteka::Szukaj_Ksiazki_ID(int input_ID_Ksiazki) {
	
	auto i = Zasoby.begin(), end = Zasoby.end();
	do {
		find_if(i, end, [&](Ksiazka k) {return k.GetID()  == input_ID_Ksiazki; })->Drukuj();
		i++;
	} while (i != end);

	find_if(Zasoby.begin(), Zasoby.end(), [&](Ksiazka* k) {return k->GetID() == input_ID_Ksiazki; })->Drukuj();
}*/