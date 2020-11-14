//#include "Nodo.h"
#include<iostream>
#include "Citta.h"
#include "Macchina.h"
#include "Dio.h"

int main(){
    std::cout<<"Inizio"<<"\n";
    //std::cout<<c.insieme_nodi[2].nome();

   Macchina macchine[N_MACCHINE];

   Dio::crea_citta(0.5);
   Dio::crea_percorso();
   

   for (int i = 0; i < N_MACCHINE; i++){
      macchine[i] = Macchina();
   }

   
   while (Dio::_macchine_a_destinazione < N_MACCHINE){
      for (int i = 0; i < N_MACCHINE; i++){
         std::cout << "Muovo la macchina " << i << "\n"; 
         if (!(macchine[i].destinazione_raggiunta)){
            Dio::muovi_macchina(macchine[i], i);
         }
      }  
   }


}

