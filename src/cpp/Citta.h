
#ifndef CITTA_H
#define CITTA_H

#include "Strada.h"
#include "Nodo.h"
#include <list>
#include <string>
#include <cmath>
#include<iostream>
#include<fstream>

struct Citta {
    Strada** matrice_adiacenza;
    Nodo** path;
    int** distance;
    std::list<Nodo> print_path(Nodo source, Nodo destination);
    std::string elenco;
    short n_righe;
    short n_colonne;

    Nodo* insieme_nodi;
    //public:
    Citta();
    Citta(short n_righe, short n_colonne, float probabilita_senso_unico);
    void floyd_warshall();
};

#endif