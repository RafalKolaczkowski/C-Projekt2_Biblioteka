#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Biblioteka.h"
#include "RandomGenerator.h"

using namespace std;

class Ksiazka;

class Konto													//Stworzone sa dwa typy Konta, student (czas na oddanie ksiazki 30 dni) i pracownik uczelni (czas na oddanie ksiazki 90 dni)
{
private:
	string Nazwisko;
	int ID;
	int Naleznosc = 0;										//Kwota do zaplaty za zaleganie z oddawaniem ksiazek
public:
	Konto() {}												//Konstruktor domyslny potrzebny dla zainicjowania wektora bez inicjowania jego zawartosci od razu
	Konto(string input_Nazwisko, int input_ID)
		:Nazwisko(input_Nazwisko), ID(input_ID) {}

	vector<Ksiazka> Wypozyczone;							//Spis ksiazek, ktore zostaly wypozyczone przez wlasciciel konta

	const string Get_Nazwisko() const { return Nazwisko; }
	const int Get_ID() const { return ID; }
	virtual const bool Get_przywileje() const = 0;
	const int Get_Naleznosc() const { return Naleznosc; }
	void Set_Naleznosc(int input_Naleznosc) { Naleznosc = input_Naleznosc; }

	virtual void Drukuj() const = 0;
};

class Student :public Konto
{
private:
	bool przywileje = 0;									//Brak przywileju do 90 dniowego wypozyczania ksiazek
public:
	Student(string input_Nazwisko, int input_ID)
		:Konto(input_Nazwisko, input_ID) {}

	virtual void Drukuj() const { cout << Get_Nazwisko() << "\t" << Get_ID() << "\t" << "Student" << endl; }
	virtual const bool Get_przywileje() const { return przywileje; }
};

class Pracownik :public Konto
{
private:
	bool przywileje = 1;									//Przywilej do 90 dniowego wypozyczania ksiazek
public:
	Pracownik(string input_Nazwisko, int input_ID)
		:Konto(input_Nazwisko, input_ID) {}

	virtual void Drukuj() const { cout << Get_Nazwisko() << "\t" << Get_ID() << "\t" << "Pracownik" << endl; }
	virtual const bool Get_przywileje() const { return przywileje; }
};