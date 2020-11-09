#ifndef CITTA_H
#define CITTA_H

#include"Strada.h"
#include"Nodo.h"

const short n_colonne = 2;
const short n_righe = 0;

struct Città {
    Strada matrice_adiacenza[n_righe][n_colonne];
    Nodo insieme_nodi[n_righe*n_colonne];
    //public:
    Città(float probabilità_senso_unico);
};

#endif