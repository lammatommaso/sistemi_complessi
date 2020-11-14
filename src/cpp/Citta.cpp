#include "Citta.h"
#include <cmath>
#include<iostream>

const Strada strada_inesistente(-1);
const Strada strada_esistente(0);

void Citta::floyd_warshall(){
        for (int i = 0; i < n_righe*n_colonne; i++){
            for (int j = 0; j < n_righe*n_colonne; j++){
                if (i == j){
                    distance[i][j] = 0;
                    path[i][j] = Strada(n_righe*n_colonne);
                } else if (matrice_adiacenza[i][j].contatore() == -1){ //strada inesistente
                    distance[i][j] = NULL;
                    path[i][j] = Strada(n_righe*n_colonne);
                } else {
                    distance[i][j] = 1; //tutte le strade ora hanno peso 1
                    path[i][j] = Strada(i);
                }
            }
        }
        /**************************************************/
        for (int k = 0; k < n_righe*n_colonne; k++){
            for (int i = 0; i < n_righe*n_colonne; i++){
                for (int j = 0; j < n_righe*n_colonne; j++){
                    if (distance[i][j] != NULL && distance[i][k] != NULL && distance[k][j] != NULL ){
                        if (distance[i][j] > distance[i][k] + distance[k][j]){
                            distance[i][j] = distance[i][k] + distance[k][j];
                            path[i][j] = path[k][j];
                        }
                    }
                }
            }
        }
   }

std::list<Nodo> Citta::print_path(Nodo source, Nodo destination){

    if (source.nome() >= n_righe*n_colonne || destination.nome() >= n_righe*n_colonne){
        std::list<Nodo> optimal_path;
        return optimal_path;
    }

    if (path[source.nome()][destination.nome()].contatore() == n_righe*n_colonne){
        std::list<Nodo> optimal_path;
        return optimal_path;
    }

    std::list<Nodo> optimal_path= std::list<Nodo>();

    optimal_path.push_front(destination);

    while(path[source.nome()][destination.nome()].contatore() != source.nome()){
        optimal_path.push_back(path[source.nome()][destination.nome()].contatore());
    }
    return optimal_path;
}

Citta::Citta() {
    ;;
};

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

    floyd_warshall();

}