#ifndef CITTA_H
#define CITTA_H

#include"Strada.h"
#include"Nodo.h"
#include <list>

const short n_colonne = 6; //righe e colonne del reticolo, non della matrice di adiacenza
const short n_righe = 6;

struct Citta {
    Strada matrice_adiacenza[n_righe*n_colonne][n_righe*n_colonne];
    Nodo path[n_righe*n_colonne][n_righe*n_colonne];
    int distance[n_righe*n_colonne][n_righe*n_colonne];
    std::list<Nodo> print_path(Nodo source, Nodo destination);

    Nodo insieme_nodi[n_righe*n_colonne];
    //public:
    Citta();
    Citta(float probabilita_senso_unico);
    void floyd_warshall();
};

#endif