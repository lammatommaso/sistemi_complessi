#ifndef NODO_H
#define NODO_H

class Nodo {
  short _nome;

  public:
  int nome() const { return _nome; }
  void cambia_nome(short nome){_nome = nome;}
  Nodo() : _nome(-1) {}
  Nodo(int i) : _nome(i) {}
  Nodo(Nodo const& nodo) : _nome(nodo._nome) {} 
};

#endif




















//#include "Globali.h"
//bool puoi_attraversare(); //se semaforo è spento o acceso
  /*
   * bool puoi_attraversare(int a, int b){
   *    if (this.incrocio() == true){
   *      sem.P();
   *      if (semaforo == verde)
   *          sem.v(); return true;
   *        else
   *          sem.V(); return false;
   *    }
   *  }
   * NOTA: il nodo potrebbe essere una semplice congiunzione tra due strade: ----o-----
   * in quel caso puoi_attraversare dovrebbe solo restituire b.sono_pieno()
  */