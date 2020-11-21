
#ifndef CITTA_H
#define CITTA_H

#include "Strada.h"
#include "Nodo.h"
#include <list>
#include <string>
#include <cmath>
#include<iostream>

const short n_colonne = 20; //righe e colonne del reticolo, non della matrice di adiacenza
const short n_righe = 20;

struct Citta {
    Strada matrice_adiacenza[n_righe*n_colonne][n_righe*n_colonne];
    Nodo path[n_righe*n_colonne][n_righe*n_colonne];
    int distance[n_righe*n_colonne][n_righe*n_colonne];
    std::list<Nodo> print_path(Nodo source, Nodo destination);
    std::string elenco;

    Nodo insieme_nodi[n_righe*n_colonne];
    //public:
    Citta();
    Citta(float probabilita_senso_unico);
    void floyd_warshall();
};

#endif