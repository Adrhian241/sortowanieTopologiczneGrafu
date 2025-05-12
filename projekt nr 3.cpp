#include <iostream>
#include "Graf.h"
using namespace std;
int main()
{
    Graf g(7);

    g.dodajKrawedz(0, 1);
    g.dodajKrawedz(1, 2);
    g.dodajKrawedz(2, 4);
    g.dodajKrawedz(2, 5);
    g.dodajKrawedz(0, 6);
    g.dodajKrawedz(6, 5);
    g.dodajKrawedz(0, 3);
    g.dodajKrawedz(3, 1);
   
    cout << "graf wypisany jako macierz dwuwymiarowa: " << endl;
    g.print();

    if (g.sortowanieTopologiczne())
    {
        cout << "znaleziono cykl, nie mozna posortowac grafu topologicznie" << endl;
    }
    else {
        cout << "Graf jest acykliczny." << endl;
    }
    return 0;
}
