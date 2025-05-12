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
	if (u >= 0 && u <= liczbaWierzcholkow && v >= 0 && v <= liczbaWierzcholkow)
	{
		macierzSasiedztwa[u][v] = 1;
	}
}
bool Graf::DFS(int v, int* odwiedzone, int* porzadekTopologiczny, int& indeks) {
	odwiedzone[v] = 1; // wierzcho³ek jest w trakcie odwiedzania (on stack)

	// Odwiedzamy wszystkich s¹siadów
	for (int i = 0; i <liczbaWierzcholkow; i++) {
		if (macierzSasiedztwa[v][i] == 1) { // sprawdzamy krawêdŸ
			if (odwiedzone[i] == 1) {
				return true; // cykl znaleziony (wracamy do wierzcho³ka w trakcie odwiedzania)
			}
			if (odwiedzone[i] == 0 && DFS(i, odwiedzone, porzadekTopologiczny, indeks)) {
				return true; // cykl znaleziony w rekursji
			}
		}
	}
	odwiedzone[v] = 2; // wierzcho³ek ca³kowicie odwiedzony
	porzadekTopologiczny[indeks++] = v; // dodajemy wierzcho³ek do porz¹dku topologicznego
	return false;
}
bool Graf::sortowanieTopologiczne() {
	int* porzadekTopologiczny = new int[liczbaWierzcholkow];
	int* odwiedzone = new int[liczbaWierzcholkow];
	int indeks = 0; // indeks do zapisywania w porz¹dku topologicznym
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		odwiedzone[i] = 0; // wszystkie wierzcho³ki na pocz¹tku s¹ nieodwiedzone
	}

	// Odpalamy DFS dla ka¿dego nieodwiedzonego wierzcho³ka
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		if (odwiedzone[i] == 0) {
			if (DFS(i, odwiedzone, porzadekTopologiczny, indeks)) {
				delete[] odwiedzone;
				delete[] porzadekTopologiczny;
				return true; // jeœli znaleziono cykl, zwracamy true
			}
		}
	}

	// Wypisujemy porz¹dek topologiczny (odwrócony porz¹dek zapisany w tablicy)
	cout << "Porzadek topologiczny: ";
	for (int i = liczbaWierzcholkow - 1; i >= 0; i--) {
		cout << porzadekTopologiczny[i] << " ";
	}
	cout << endl;

	delete[] odwiedzone;
	delete[] porzadekTopologiczny;
	return false; // brak cyklu, sortowanie topologiczne zakoñczone pomyœlnie
}
