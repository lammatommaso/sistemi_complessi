

#ifndef DIO_H
#define DIO_H

#include "Macchina.h"
#include "Citta.h"
#include "Nodo.h"
#include <list>
#include <time.h>
#include <iostream>
#define N_MACCHINE 500

class Dio{

    short _macchine_a_destinazione = 0;
    std::list<Nodo> percorsi[N_MACCHINE]; 
    Citta c;
    Nodo posizione_macchine[N_MACCHINE];
    Macchina* macchine[N_MACCHINE];
    void muovi_macchina(int indice_macchina );
    inline Nodo trova_next(int indice_macchina)const;
    inline Strada associa_strada(int indice_macchina)const;

public:

    Dio();    
    
    void crea_citta(float p);
    void crea_percorso();
    void avvia_macchine();
};

#endif