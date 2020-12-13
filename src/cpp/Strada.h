#ifndef STRADA_H
#define STRADA_H

class Strada {
  short _contatore; //Una strada non esiste se ha contatore -1
  static const short _lunghezza = 50; 

  public:
  short contatore() const { return _contatore; }
 
  Strada() : _contatore(0) {}
  Strada(int contatore) : _contatore(contatore){}
  Strada(Strada const& strada) : _contatore(strada._contatore){}
  static short lunghezza(){return _lunghezza;}
  void aggiungi_macchina() { _contatore++; }
  void togli_macchina() { _contatore--; }
};

//void operator= ()

#endif




  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  //bool sono_pieno() const { return n_auto_attuale == lunghezza_std; };
