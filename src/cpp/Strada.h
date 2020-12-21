#ifndef STRADA_H
#define STRADA_H
#include<random>

class Strada {
    short _contatore; //Una strada non esiste se ha contatore -1
    short _lunghezza;
  public:
    short contatore()const;
    //Strada() : _contatore(0), _lunghezza(10){}
    Strada();
    Strada(int contatore);
    Strada(Strada const& strada);
    short lunghezza();
    short contatore(){return _contatore;}
    void aggiungi_macchina();
    void togli_macchina();
};

//void operator= ()

#endif




  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  //bool sono_pieno() const { return n_auto_attuale == lunghezza_std; };
