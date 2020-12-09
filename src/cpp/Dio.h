

#ifndef DIO_H
#define DIO_H

#include "Macchina.h"
#include "Citta.h"
#include "Nodo.h"
#include <list>
#include <time.h>
#include <iostream>
#define N_MACCHINE 500

//namespace Dio{

    extern short _macchine_a_destinazione;
    extern std::list<Nodo> percorsi[N_MACCHINE]; 
    extern Citta c;
    extern Nodo posizione_macchine[N_MACCHINE];

    //TODO crea array di offset per sapere in che punto della strada è la macchina

    void crea_citta(float p);

    void muovi_macchina( Macchina *m, int indice_macchina );

    void crea_percorso();
//}

#endif