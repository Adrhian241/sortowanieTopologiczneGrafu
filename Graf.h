#pragma once
class Graf
{
    private:
        int liczbaWierzcholkow;
        int** macierzSasiedztwa;
    public:
        //konstruktor
        Graf(int wierzcholki);
        //destruktor
        ~Graf();
        //wyswietlanie
        void print();
        //dodawanie krawedzi, graf skierowany
        void dodajKrawedz(int u, int v);
        
        bool DFS(int v, int* odwiedzone, int* porzadekTopologiczny, int& indeks);
        
        bool sortowanieTopologiczne();
};

