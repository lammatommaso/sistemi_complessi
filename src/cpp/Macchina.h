#ifndef MACCHINA_H
#define MACCHINA_H

#include<time.h>
#include<iostream>

const short ritardo_massimo = 0;

class Macchina {
    short _passi;
    short _passi_locali;
    bool _destinazione_raggiunta;
    short _ritardo;
public:
    Macchina();
    Macchina(short passi);
    Macchina(Macchina const& macchina);
    void passo_avanti();
    void reset_passi_locali();
    void riduci_ritardo();
    void set_destinazione_raggiunta(bool raggiunta);
    bool destinazione_raggiunta()const;
    short ritardo()const;
    short passi()const;
    short passi_locali()const;
};

#endif





























































 /* std::list<Nodo> percorso; //es. 1 - 10: 1, 3, 5, 8, 2, 10
    int posizione = 0;

    Nodo[2] prima_strada; //Delegata al costruttore
    Nodo* strada_attuale() const;
    Nodo* strada_futura() const;
    //int velocità, offset; ...
    int passi_locali = 0; //aumenta di 1 tutte le volte che faccio un passo - cioè puoi_attraversare == true, deve essere annullata ogni volta che intra in una strada nuova
    int cicli_persi; //aumenta di 1 tutte le volte che perdo un ciclo - cioè puoi_attraversare == false
    //consideriamo il rapporto passi/(passi + cicli_persi)

  public:
    void vai_avanti();
    /* avanza con l'offset OPPURE se siamo in fondo alla strada chiama
     * strada_attuale[1].vai_avanti()
     * vai_avanti(){
     *  if (puoi_attraversare(b,c))
     *    strada_attuale = (c,d)
     *  }
     * }
     */ 
