#ifndef STRADA_H
#define STRADA_H
#include<random>

const short media_gaussiana = 20;
const short sigma_gaussiana = 10;
const short lunghezza_minima = 5;
const short lunghezza_massima = 30;

class Strada {
    short _contatore; //Una strada non esiste se ha contatore -1
    short _lunghezza;
public:
    short contatore()const;
    Strada();
    Strada(short contatore);
    Strada(Strada const& strada);
    short lunghezza();
    short contatore(){return _contatore;}
    void aggiungi_macchina();
    void togli_macchina();
};
#endif




  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  //bool sono_pieno() const { return n_auto_attuale == lunghezza_std; };
