#include "Dio.h"
//using namespace Dio;

    bool ordine(Macchina* i, Macchina* j)
    {
        return (i->passi_locali() > j->passi_locali());
    }

    
    Dio::Dio()
    {
        for (int i = 0; i < N_MACCHINE; i++)
        {
            macchine.push_back(new Macchina());
        }
    }

    void Dio::crea_citta(short n_righe, short n_colonne, float p){
        c = Citta(n_righe, n_colonne, p);
    }

    Strada Dio::associa_strada(int indice_macchina)const
    {     
        return c.matrice_adiacenza[posizione_macchine[indice_macchina].nome()][trova_next(indice_macchina).nome()];
    }

    Nodo Dio::trova_next(int indice_macchina)const
    {
        bool fine_ricerca = false;
        Nodo next;
        for (Nodo n : percorsi[indice_macchina])
        {
            next = n;
            
            if (fine_ricerca){
                break;
            }

            if (n.nome() == posizione_macchine[indice_macchina].nome()){
                fine_ricerca = true;
            } 
        }

        return next;
    }

    void Dio::muovi_macchina( int indice_macchina ){
        std::list<Nodo> percorso = percorsi[indice_macchina];
  
        Nodo next=trova_next(indice_macchina);

            //if(m->passi_locali() < associa_strada(indice_macchina).lunghezza())
        if(macchine[indice_macchina]->passi_locali()<associa_strada(indice_macchina).lunghezza())
        {                
            bool puo_andare_avanti = 1;

            for(int i=0;i<N_MACCHINE;i++)
            {
                if(posizione_macchine[indice_macchina].nome()==posizione_macchine[i].nome()
                       &&  trova_next(indice_macchina).nome()==trova_next(i).nome())
                {
                    puo_andare_avanti = macchine[indice_macchina]->passi_locali() != macchine[i]->passi_locali() - 1;
                    if(puo_andare_avanti == 0) break;
                }
            }
            if(puo_andare_avanti)
            {
                macchine[indice_macchina]->passo_avanti();
                //std::cout<<"Passo avanti"<<"\n";
            }
            else
            {
                std::cout<<"Non mi muovo"<<"\n";
            }
        }
        else
        {            
            posizione_macchine[indice_macchina] = next;
            macchine[indice_macchina]->reset_passi_locali();
        }


        if (posizione_macchine[indice_macchina].nome() == percorso.back().nome()){
            _macchine_a_destinazione++;
            macchine[indice_macchina]->destinazione_raggiunta = true;
            //std::cout << "La macchina " << indice_macchina << " ha raggiunto la destinazione! \n";
        }
        /* if (m->passi()/Strada::lunghezza() == percorso.size()){
            _macchine_a_destinazione++;
            m->destinazione_raggiunta = true;
            std::cout << "La macchina " << indice_macchina << " ha raggiunto la destinazione! \n";
        }*/
    }

    void Dio::crea_percorso(){
        srand(time(NULL));
        
        for (int i = 0; i < N_MACCHINE; i++){
            Nodo a, b;
            do{
            a = c.insieme_nodi[rand()%(c.n_righe*c.n_colonne)];
            b = c.insieme_nodi[rand()%(c.n_righe*c.n_colonne)];
            }while(a.nome() == b.nome());
            posizione_macchine[i] = a;
            percorsi[i] = c.print_path(a, b); //nel path manca il nodo sorgente!
            percorsi[i].push_front(a);
        }
        // C'è qualcosa che non va nell'inizializzazione di percorsi o posizione_macchine
        
    }

    void Dio::avvia_macchine()
    {
        while (_macchine_a_destinazione < N_MACCHINE)
        {
            for (int i = 0; i < N_MACCHINE; i++)
            {
            //std::cout << "Muovo la macchina " << i << "\n"; 
                if (!(macchine[i]->destinazione_raggiunta) && macchine[i]->ritardo == 0)
                {
                    muovi_macchina(i);
                }
                else
                {
                    macchine[i]->ritardo--;
                }
            }  
            std::sort(macchine.begin(), macchine.end(), ordine);
        }
        int mean{0};
        for (int i = 0; i < N_MACCHINE; i++){
        mean+=macchine[i]->passi();
        }

        std::cout<<" La media dei passi è "<<mean/(int)N_MACCHINE<<std::endl;
    }

    

