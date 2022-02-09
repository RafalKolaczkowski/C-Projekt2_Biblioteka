#pragma once

#include <iostream>
#include <string>
#include "RandomGenerator.h"
#include <vector>
#include "Konta.h"
#include <memory>
#include <iterator>

using namespace std;

class Ksiazka
{
private:
	string Nazwa;
	int ID;
	int Filia_ID;
	bool wymagane_uprawnienia;
	bool stan_wypozyczenia;
	int czas_do_oddania;
	int ID_Konta_Wypozyczajacego;
public:
	Ksiazka(string input_Nazwa, int input_ID, int input_Filia_ID, bool input_wymagane_uprawnienia)
		:Nazwa(input_Nazwa), ID(input_ID), Filia_ID(input_Filia_ID), wymagane_uprawnienia(input_wymagane_uprawnienia), stan_wypozyczenia(0), czas_do_oddania(0), ID_Konta_Wypozyczajacego(0) {}

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
			cout << endl;
	}
};

class Biblioteka
{
private:
	int Liczba_Filii;
	int Liczba_Kont = 0;
	vector<unique_ptr<Konto>> ListaKont;
	//Konto* ListaKont[1000];
	//vector<unique_ptr<Ksiazka>> Zasoby;
	//Ksiazka* Zasoby[1000];
	//vector<Filia> ListaFilii;
	vector <Ksiazka> Zasoby;
public:
	Biblioteka() {}
	Biblioteka(int input_Liczba_Filii, int input_Liczba_Kont)
		: Liczba_Filii(input_Liczba_Filii) {
		Inicjalizacja_Biblioteki(input_Liczba_Kont, Liczba_Filii);}

	void Inicjalizacja_Biblioteki(int N_Kont, int N_Filii);
	void Dodaj_Konto(bool typ, string Nazwisko);
	void Drukuj_Zasoby();
	void Drukuj_Konta();
	void Drukuj_Wypozyczenia_Konta(int Numer_Studenta);

	void Wypozycz(int input_ID_ksiazki, int Numer_Studenta);
	void Oddaj(int input_ID_ksiazki);
	void Oddaj_Naleznosc(int input_ID_konta);
	void Przedluz_Ksiazki(int input_ID_konta);
	void Aktualizuj_Stan_Wypozyczenia(int dlugosc_tury);
	const int Drukuj_Naleznosc(int input_Numer_Konta) const { return ListaKont[input_Numer_Konta]->Get_Naleznosc(); }

	const int Get_Liczba_Kont()const { return Liczba_Kont; }
	const int Get_Liczba_Ksiazek()const { return Zasoby.size(); }

	static const int Naleznosc = 1;		//20 groszy za dzien za ksiazke
	//void Szukaj_Ksiazki_ID(int input_ID_Ksiazki);					//zwraca indeks w wektorze Zasoby
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
			//ListaKont[i] = new Student(Random_Name(), 100 + i);	//przewidziane 100 miejsc na konta studentow
			ListaKont.emplace_back(new Student(Random_Name(), 100 + Liczba_Studentow));
			Liczba_Studentow++;
		}
		else
		{
			//ListaKont[i] = new Pracownik(Random_Name(), 200 + i);	//przewidziane 100 miejsc na konta pracownikow
			ListaKont.emplace_back(new Pracownik(Random_Name(), 200 + Liczba_Pracownikow));
			Liczba_Pracownikow++;
		}
		Liczba_Kont++;
	}
	for (int i = 0; i < N_Filii; i++)
	{
		for (int j = 0; j < Random_Book_Number(); j++)
		{
			Zasoby.emplace_back(Random_Book_Name(), Numer_ksiazki, i, Random_Privileges());
			Numer_ksiazki++;
		}
	}
}

void Biblioteka::Dodaj_Konto(bool typ, string Nazwisko)
{
	int Liczba_Pracownikow = count_if(ListaKont.begin(), ListaKont.end(), [](unique_ptr<Konto>& k) {return k->Get_ID() >= 200; });
	int Liczba_Studentow = count_if(ListaKont.begin(), ListaKont.end(), [](unique_ptr<Konto>& k) {return k->Get_ID() < 200; });
	if (typ == 0)
	{
		ListaKont.emplace_back(new Student(Nazwisko, 100 + Liczba_Studentow));
		Liczba_Kont++;
	}
	else
	{
		ListaKont.emplace_back(new Pracownik(Nazwisko, 200 + Liczba_Pracownikow));
		Liczba_Kont++;
	}
}

void Biblioteka::Drukuj_Zasoby()
{
	//for (auto i : Zasoby)
	//for_each(Zasoby.begin(), Zasoby.end(), [](Ksiazka* ep) {ep->Drukuj(); });
	cout << "Filia_ID" << "\t" << "Nazwa" << "\t\t\t\t\t\t\t" << "ID" << "\t" << "stan_wyp." << "\t" << "czas_do_oddania" << "\t" << "ID konta" << endl;
	for (int i = 0; i < Zasoby.size(); ++i) { Zasoby[i].Drukuj(); }
}

void Biblioteka::Drukuj_Konta()
{
	//for (auto i : Zasoby)
	//for_each(Zasoby.begin(), Zasoby.end(), [](Ksiazka* ep) {ep->Drukuj(); });
	cout << "Numer na liscie" << "\t" << "Imie" << "\t" << "Nazwisko" << "\t" << "ID" << "\t" << "Typ" << endl;
	for (int i = 0; i < ListaKont.size(); ++i) 
	{ 
		cout << i << "\t\t";
		ListaKont[i]->Drukuj(); 
	}
}

void Biblioteka::Drukuj_Wypozyczenia_Konta(int Numer_Studenta)
{
	for (int i = 0; i < ListaKont[Numer_Studenta]->Wypozyczone.size(); i++)
		ListaKont[Numer_Studenta]->Wypozyczone[i].Drukuj();
}

void Biblioteka::Wypozycz(int input_ID_ksiazki, int Numer_Studenta)
{
	if (Zasoby[input_ID_ksiazki].Get_stan_wypozyczenia() == 1)
		cout << "Przykro nam, ale ksiazka jest juz wypozyczona" << endl;
	else
	{
		Zasoby[input_ID_ksiazki].Set_stan_wypozyczenia(1);
		Zasoby[input_ID_ksiazki].Set_ID_Konta_Wypozyczajacego(Numer_Studenta);
		if(ListaKont[Numer_Studenta]->Get_przywileje()==0)
			Zasoby[input_ID_ksiazki].Set_czas_do_oddania(30);
		else
			Zasoby[input_ID_ksiazki].Set_czas_do_oddania(90);
		ListaKont[Numer_Studenta]->Wypozyczone.emplace_back(Zasoby[input_ID_ksiazki]);
	}
}

void Biblioteka::Oddaj(int input_ID_ksiazki)
{
	int ID_konta = Zasoby[input_ID_ksiazki].Get_ID_Konta_Wypozyczajacego();
	auto id = find_if(ListaKont[ID_konta]->Wypozyczone.begin(), ListaKont[ID_konta]->Wypozyczone.end(), [&](Ksiazka k) {return k.GetID() == input_ID_ksiazki; });
	int index = distance(ListaKont[ID_konta]->Wypozyczone.begin(), id);
	ListaKont[ID_konta]->Wypozyczone.erase(ListaKont[ID_konta]->Wypozyczone.begin()+index);
	Zasoby[input_ID_ksiazki].Set_stan_wypozyczenia(0);
	Zasoby[input_ID_ksiazki].Set_ID_Konta_Wypozyczajacego(NULL);
	Zasoby[input_ID_ksiazki].Set_czas_do_oddania(0);
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
			ListaKont[input_ID_konta]->Wypozyczone[i].Set_czas_do_oddania(ListaKont[input_ID_konta]->Wypozyczone[i].Get_czas_do_oddania() + 30);
		else
			ListaKont[input_ID_konta]->Wypozyczone[i].Set_czas_do_oddania(ListaKont[input_ID_konta]->Wypozyczone[i].Get_czas_do_oddania() + 90);
	}
}

void Biblioteka::Aktualizuj_Stan_Wypozyczenia(int dlugosc_tury)
{
	for (int i = 0; i < Zasoby.size(); i++)
	{
		if (Zasoby[i].Get_stan_wypozyczenia() == 1 && Zasoby[i].Get_czas_do_oddania() >= 5)
		{
			Zasoby[i].Set_czas_do_oddania(Zasoby[i].Get_czas_do_oddania() - dlugosc_tury);
			//ListaKont[Zasoby[i].Get_ID_Konta_Wypozyczajacego()]->Wypozyczone.size();
		}
	}
	for (int i = 0; i < ListaKont.size(); i++)
	{
		for (int j = 0; j < ListaKont[i]->Wypozyczone.size(); j++)
		{
			if (ListaKont[i]->Wypozyczone[j].Get_czas_do_oddania() >= 5)
				ListaKont[i]->Wypozyczone[j].Set_czas_do_oddania(ListaKont[i]->Wypozyczone[j].Get_czas_do_oddania() - dlugosc_tury);
			else
				ListaKont[i]->Set_Naleznosc(ListaKont[i]->Get_Naleznosc()+Naleznosc);
		}
	}
}

//void Biblioteka::Szukaj_Ksiazki_ID(int input_ID_Ksiazki){
/*	vector<int> indeksy;
	
	auto i = Zasoby.begin(), end = Zasoby.end();
	do {
		auto it = std::find_if(i, end, [&](unique_ptr<Konto>& k) {return k->Get_ID() == input_ID_Ksiazki; });
		indeksy.emplace_back(distance(Zasoby.begin(), it));
		//indeksy.emplace_back(distance(Zasoby.begin(), find_if(i, end, [&](unique_ptr<Konto>& k) {return k->Get_ID()== input_ID_Ksiazki; })));
		i++;
	} while (i != end);
	for (int j = 0; j < indeksy.size(); j++)
		Zasoby[indeksy[j]].Drukuj();*/

	/*auto i = Zasoby.begin(), end = Zasoby.end();
	do {
		find_if(i, end, [&](Ksiazka k) {return k.GetID()  == input_ID_Ksiazki; })->Drukuj();
		i++;
	} while (i != end);*/

	//find_if(Zasoby.begin(), Zasoby.end(), [&](Ksiazka* k) {return k->GetID() == input_ID_Ksiazki; })->Drukuj();}