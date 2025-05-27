#include "Graf.h"
#include <iostream>
using namespace std;
Graf::Graf(int wierzcholki)
{
	liczbaWierzcholkow = wierzcholki;
	macierzSasiedztwa = new int* [liczbaWierzcholkow];
	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		macierzSasiedztwa[i] = new int[liczbaWierzcholkow];
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			macierzSasiedztwa[i][j] = 0;
		}
	}
}
Graf::~Graf() {
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		delete[] macierzSasiedztwa[i];
	}
	delete[] macierzSasiedztwa;
}
void Graf::print()
{
	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		for (int j = 0; j < liczbaWierzcholkow; j++)
		{
			cout << macierzSasiedztwa[i][j] << " ";
		}
		cout << endl;
	}
}
void Graf::dodajKrawedz(int u, int v)
{
	if (u >= 0 && u < liczbaWierzcholkow && v >= 0 && v < liczbaWierzcholkow)
	{
		macierzSasiedztwa[u][v] = 1;
	}
}
bool Graf::DFS(int v, int* odwiedzone, int* porzadekTopologiczny, int& indeks) {
	odwiedzone[v] = 1; // wierzchołek jest w trakcie odwiedzania (on stack)

	// Odwiedzamy wszystkich sąsiadów
	for (int i = 0; i <liczbaWierzcholkow; i++) {
		if (macierzSasiedztwa[v][i] == 1) { // sprawdzamy krawędź
			if (odwiedzone[i] == 1) {
				return true; // cykl znaleziony (wracamy do wierzchołka w trakcie odwiedzania)
			}
			if (odwiedzone[i] == 0 && DFS(i, odwiedzone, porzadekTopologiczny, indeks)) {
				return true; // cykl znaleziony w rekursji
			}
		}
	}
	odwiedzone[v] = 2; // wierzchołek całkowicie odwiedzony
	porzadekTopologiczny[indeks++] = v; // dodajemy wierzchołek do porządku topologicznego
	return false;
}
bool Graf::sortowanieTopologiczne() {
	int* porzadekTopologiczny = new int[liczbaWierzcholkow];
	int* odwiedzone = new int[liczbaWierzcholkow];
	int indeks = 0; // indeks do zapisywania w porządku topologicznym
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		odwiedzone[i] = 0; // wszystkie wierzchołki na początku są nieodwiedzone
	}

	// Odpalamy DFS dla każdego nieodwiedzonego wierzchołka
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		if (odwiedzone[i] == 0) {
			if (DFS(i, odwiedzone, porzadekTopologiczny, indeks)) {
				delete[] odwiedzone;
				delete[] porzadekTopologiczny;
				return true; // jeśli znaleziono cykl, zwracamy true
			}
		}
	}

	// Wypisujemy porządek topologiczny (odwrócony porządek zapisany w tablicy)
	cout << "Porzadek topologiczny: ";
	for (int i = liczbaWierzcholkow - 1; i >= 0; i--) {
		cout << porzadekTopologiczny[i] << " ";
	}
	cout << endl;

	delete[] odwiedzone;
	delete[] porzadekTopologiczny;
	return false; // brak cyklu, sortowanie topologiczne zakończone pomyślnie
}
