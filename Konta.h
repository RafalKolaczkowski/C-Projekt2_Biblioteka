#pragma once

#include <iostream>
#include <string>
#include "RandomGenerator.h"
#include <vector>
#include "Biblioteka.h"
#include <memory>

using namespace std;

class Ksiazka;

class Konto
{
private:
	string Nazwisko;
	int ID;
	int Naleznosc = 0;
public:
	Konto() {}
	Konto(string input_Nazwisko, int input_ID)
		:Nazwisko(input_Nazwisko), ID(input_ID) {}

	vector<Ksiazka> Wypozyczone;

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
	bool przywileje = 0;
public:
	Student(string input_Nazwisko, int input_ID)
		:Konto(input_Nazwisko, input_ID) {}

	virtual void Drukuj() const { cout << Get_Nazwisko() << "\t" << Get_ID() << "\t" << "Student" << endl; }
	virtual const bool Get_przywileje() const { return przywileje; }
};

class Pracownik :public Konto
{
private:
	bool przywileje = 1;
public:
	Pracownik(string input_Nazwisko, int input_ID)
		:Konto(input_Nazwisko, input_ID) {}

	virtual void Drukuj() const { cout << Get_Nazwisko() << "\t" << Get_ID() << "\t" << "Pracownik" << endl; }
	virtual const bool Get_przywileje() const { return przywileje; }
};