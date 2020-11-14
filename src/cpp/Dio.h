#ifndef DIO_H
#define DIO_H

#include "Macchina.h"
#include "Citta.h"
#include "Nodo.h"
#include <list>
#include <time.h>
#include <iostream>
#define N_MACCHINE 10

namespace Dio{

    short _macchine_a_destinazione = 0;
    std::list<Nodo> percorsi[N_MACCHINE]; 
    Citta c;
    Nodo posizione_macchine[N_MACCHINE];
    //TODO crea array di offset per sapere in che punto della strada è la macchina

    void crea_citta(float p){
        c = Citta(p);
    }

    void muovi_macchina( Macchina m, int indice_macchina ){
        std::list<Nodo> percorso = percorsi[indice_macchina];
        Nodo posizione_attuale = posizione_macchine[indice_macchina];

        bool fine = false;
        int passi_lista;
        for (Nodo n : percorso){
            passi_lista++;

            if (fine){
                posizione_macchine[indice_macchina] = n;
                m.passo_avanti();
                break;
            }

            if (n.nome() == posizione_attuale.nome()){
                fine = true;
            } 
        }
    
        if (passi_lista == percorso.size()-1 ){
            _macchine_a_destinazione++;
            m.destinazione_raggiunta = true;
            std::cout << "La macchina " << indice_macchina << " ha raggiunto la destinazione! \n";
        }
    }

    void crea_percorso(){
        srand(time(NULL));
        
        for (int i = 0; i < N_MACCHINE; i++){
            
            percorsi[i] = std::list<Nodo>();
            for (int j = 0; j < (int)(rand()% 21); j++){
                Nodo a = c.insieme_nodi[rand()%n_righe*n_colonne];
                Nodo b = c.insieme_nodi[rand()%n_righe*n_colonne];
                posizione_macchine[i] = a;
                percorsi[i] = c.print_path(a, b);
            }
        }
        
    }

}

#endif