#ifndef MACCHINA_H
#define MACCHINA_H

class Macchina {
  short _passi;
  short _passi_locali;

  public:
  int nome;
  bool destinazione_raggiunta;
  Macchina() : _passi(0), _passi_locali(0), destinazione_raggiunta(false) {}
  //Macchina(short passi) : _passi(passi){}
  Macchina(Macchina const& macchina) : _passi(macchina._passi), _passi_locali(macchina._passi_locali), destinazione_raggiunta(macchina.destinazione_raggiunta) {}
  void passo_avanti() { _passi++; _passi_locali++; }
  void reset_passi_locali(){ _passi_locali = 0; }
  short passi()const{return _passi; }
  short passi_locali()const{return _passi_locali;}
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
