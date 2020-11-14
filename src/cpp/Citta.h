#ifndef CITTA_H
#define CITTA_H

#include"Strada.h"
#include"Nodo.h"

const short n_colonne = 3;
const short n_righe = 3;

struct Citta {
    Strada matrice_adiacenza[n_righe][n_colonne];
    Nodo insieme_nodi[n_righe*n_colonne];
    //public:
    Citta(float probabilita_senso_unico);
};

#endif