#include "Projekt_2.h"
#include <iostream>

using namespace std;

int main()
{
	//cout << "Hello CMake." << endl;

	Symulacja s(20,5);			//obiekt stanowiacy centrum programu. Tworzone jest losowo 20 kont i  50-100 ksiazek. Obecnie program nie jest dostosowany do wiecej niz 100 kont
	s.Symuluj();				//rozpoczyna petle symulacji dzialania Biblioteki

	return 0;
}
