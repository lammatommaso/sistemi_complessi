
#include <iostream>
#include "Citta.h"
#include "Macchina.h"
#include "Dio.h"

//using namespace Dio;

int main(){

   Dio dio;
   dio.crea_citta(3,3,0.5);
   dio.crea_percorso();
   dio.avvia_macchine();
}

