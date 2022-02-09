# CMakeList.txt: projekt CMake dla elementu Projekt_2, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("Projekt_2")

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (Projekt_2 "Projekt_2.cpp" "Projekt_2.h" "Konta.h" "Biblioteka.h" "RandomGenerator.h")

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
