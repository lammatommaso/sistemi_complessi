

#ifndef DIO_H
#define DIO_H

#include "Macchina.h"
#include "Citta.h"
#include "Nodo.h"
#include <list>
#include <time.h>
#include <iostream>
#include<vector>
#include<algorithm>
#define N_MACCHINE 1

class Dio{ 

    short _macchine_a_destinazione = 0;
    std::list<Nodo> percorsi[N_MACCHINE]; 
    Citta c;
    Nodo posizione_macchine[N_MACCHINE];
    void muovi_macchina(int indice_macchina );
    inline Nodo trova_next(int indice_macchina)const;
    inline Strada associa_strada(int indice_macchina)const;

public:
    std::vector<Macchina*> macchine;

    Dio();    
    
    void crea_citta(short n_righe, short n_colonne, float p);
    void crea_percorso();
    void avvia_macchine();
    Citta get_citta()const{return c;}
};

#endif