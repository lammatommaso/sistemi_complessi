#ifndef DIO_H
#define DIO_H

#include "Macchina.h"
#include "Citta.h"
#include "Nodo.h"
#include <list>
#include <time.h>
#include <iostream>
#define N_MACCHINE 6

namespace Dio{

    short _macchine_a_destinazione = 0;
    std::list<Nodo> percorsi[N_MACCHINE]; 
    Citta c;
    Nodo posizione_macchine[N_MACCHINE];
    //TODO crea array di offset per sapere in che punto della strada è la macchina

    void crea_citta(float p){
        c = Citta(p);
    }

    void muovi_macchina( Macchina *m, int indice_macchina ){
        std::list<Nodo> percorso = percorsi[indice_macchina];
        Nodo posizione_attuale = posizione_macchine[indice_macchina];

        bool fine = false;
        Nodo next;
        for (Nodo n : percorso){
            next = n;
            
            if (fine){
                break;
            }

            if (n.nome() == posizione_attuale.nome()){
                fine = true;
            } 
        }

        posizione_macchine[indice_macchina] = next;
        m->passo_avanti();
    
        if (m->passi() == percorso.size() ){
            _macchine_a_destinazione++;
            m->destinazione_raggiunta = true;
            std::cout << "La macchina " << indice_macchina << " ha raggiunto la destinazione! \n";
        }
    }

    void crea_percorso(){
        srand(time(NULL));
        
        for (int i = 0; i < N_MACCHINE; i++){
            
            percorsi[i] = std::list<Nodo>();
            for (int j = 0; j < (int)(rand()% 21); j++){
                percorsi[i] = std::list<Nodo>();
                while (percorsi[i].size() < 3){ //TODO c'è il rischio di loop infiniti? non credo ma è da controllare
                //TODO: la condizione < 2 significa trovami percorsi lunghi almeno 2, per debug
                    Nodo a = c.insieme_nodi[rand()%(n_righe*n_colonne)];
                    Nodo b = c.insieme_nodi[rand()%(n_righe*n_colonne)];
                    posizione_macchine[i] = a;
                    percorsi[i] = c.print_path(a, b); //nel path mancail nodo sorgente!
                    percorsi[i].push_front(a);
                }
            }
        }
        
    }

}

#endif