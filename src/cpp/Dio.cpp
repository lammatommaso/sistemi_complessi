#include "Dio.h"
//using namespace Dio;

    short _macchine_a_destinazione = 0;
    std::list<Nodo> percorsi[N_MACCHINE]; 
    Citta c;
    Nodo posizione_macchine[N_MACCHINE];

    void crea_citta(float p){
        c = Citta(p);
    }

    /*Strada associa_strada(int indice_macchina)
    {
        std::list<Nodo> percorso = percorsi[indice_macchina];
        Nodo posizione_attuale = posizione_macchine[indice_macchina];
        
        bool fine_ricerca = false;
        Nodo next;
        for (Nodo n : percorso){
            next = n;
            
            if (fine_ricerca){
                break;
            }

            if (n.nome() == posizione_attuale.nome()){
                fine_ricerca = true;
            } 
        }

        return c.matrice_adiacenza[posizione_attuale.nome()][next.nome()];

    }*/

    void muovi_macchina( Macchina *m, int indice_macchina ){
        std::list<Nodo> percorso = percorsi[indice_macchina];
        Nodo posizione_attuale = posizione_macchine[indice_macchina];

        bool fine_ricerca = false;
        Nodo next;
        for (Nodo n : percorso){
            next = n;
            
            if (fine_ricerca){
                break;
            }

            if (n.nome() == posizione_attuale.nome()){
                fine_ricerca = true;
            } 
        }

        /*bool non_ho_nessuno_davanti;
        for(int i=0;i < N_MACCHINE;i++)
        {
            if(posizione_macchine[i]=posizione_attuale)
            {
                if()//Non riesco ad accedere ai passi locali delle altre auto
            }
        }*/


        if(1)//Se non ho auto davanti
        {

            //if(m->passi_locali() < associa_strada(indice_macchina).lunghezza())
            if(m->passi_locali()<c.matrice_adiacenza[posizione_attuale.nome()][next.nome()].lunghezza())
            {
                m->passo_avanti();
            }
            else
            {
            posizione_macchine[indice_macchina] = next;
            m->reset_passi_locali();
            }

        }

        if (posizione_attuale.nome() == percorso.back().nome()){
            _macchine_a_destinazione++;
            m->destinazione_raggiunta = true;
            std::cout << "La macchina " << indice_macchina << " ha raggiunto la destinazione! \n";
        }
        /* if (m->passi()/Strada::lunghezza() == percorso.size()){
            _macchine_a_destinazione++;
            m->destinazione_raggiunta = true;
            std::cout << "La macchina " << indice_macchina << " ha raggiunto la destinazione! \n";
        }*/
    }

    void crea_percorso(){
        srand(time(NULL));
        
        for (int i = 0; i < N_MACCHINE; i++){
            
                
            Nodo a = c.insieme_nodi[rand()%(n_righe*n_colonne)];
            Nodo b = c.insieme_nodi[rand()%(n_righe*n_colonne)];
            posizione_macchine[i] = a;
            percorsi[i] = c.print_path(a, b); //nel path manca il nodo sorgente!
            percorsi[i].push_front(a);
        }
        // C'è qualcosa che non va nell'inizializzazione di percorsi o posizione_macchine
        
    }


