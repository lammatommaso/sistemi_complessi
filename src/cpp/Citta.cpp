#include "Citta.h"
#include <cmath>
#include <time.h>
#include<iostream>

const Strada strada_inesistente(-1);
const Strada strada_esistente(0);

Citta::Citta(float probabilita_senso_unico){ 
    srand(time(NULL));

    for (int i = 0; i < n_righe*n_colonne; i++ ){
        matrice_adiacenza[i][i] = strada_inesistente;
        for (int j = i+1; j < n_righe*n_colonne; j++){              
            float r = rand();
            if ((j == i+1 && j%n_colonne != 0) || j == i+n_colonne ){
                matrice_adiacenza[i][j] = strada_esistente;
                if (r/RAND_MAX > probabilita_senso_unico){
                    matrice_adiacenza[j][i] = strada_esistente;
                } else {
                    matrice_adiacenza[j][i] = strada_inesistente;                   
                }
            } else {
                matrice_adiacenza[i][j] = strada_inesistente;
                matrice_adiacenza[j][i] = strada_inesistente;
            }
        }
    }
  
    for(int i=0;i<n_righe*n_colonne;i++)
    {
        insieme_nodi[i].cambia_nome(i); 
    }
    /*
    for (int i = 0; i < n_righe*n_colonne; i++ ){
        for(int j = 0; j <= n_righe*n_colonne; j++){
            if(matrice_adiacenza[i][j] == 1) matrice_adiacenza_s[i][j] = s;
            else matrice_adiacenza_s[i][j] = s_null;
        }
    }
    */
}

int main(){
    std::cout<<"Inizio"<<"\n";
    Citta c(0.5);
    //std::cout<<c.insieme_nodi[2].nome();
}