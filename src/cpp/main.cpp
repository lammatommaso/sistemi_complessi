
#include<iostream>
#include "Citta.h"
#include "Macchina.h"
#include "Dio.h"

//using namespace Dio;

int main(){
    std::cout<<"Inizio"<<"\n";
    //std::cout<<c.insieme_nodi[2].nome();

   Macchina* macchine[N_MACCHINE];

   crea_citta(0);
   crea_percorso();
   

   for (int i = 0; i < N_MACCHINE; i++){
      macchine[i] = new Macchina();
   }

   
   while (_macchine_a_destinazione < N_MACCHINE){
      for (int i = 0; i < N_MACCHINE; i++){
         std::cout << "Muovo la macchina " << i << "\n"; 
         if (!(macchine[i]->destinazione_raggiunta)){
            muovi_macchina(macchine[i], i);
         }
      }  
   }


}

