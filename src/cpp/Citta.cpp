#include "Citta.h"

void Citta::floyd_warshall(){
        for (int i = 0; i < n_righe*n_colonne; i++){
            for (int j = 0; j < n_righe*n_colonne; j++){
                if (i == j){
                    distance[i][j] = 0;
                    path[i][j] = Nodo();
                } else if (matrice_adiacenza[i][j].contatore() == -1){ //strada inesistente
                    distance[i][j] = n_righe*n_colonne + 1; //distanza infinita
                    path[i][j] = Nodo();
                } else {
                    distance[i][j] = 1; //tutte le strade ora hanno peso 1
                    path[i][j] = Nodo(i);
                }
            }
        }
        /**************************************************/
        for (int k = 0; k < n_righe*n_colonne; k++){
            for (int i = 0; i < n_righe*n_colonne; i++){
                for (int j = 0; j < n_righe*n_colonne; j++){
                    if (distance[i][j] > distance[i][k] + distance[k][j]){
                        distance[i][j] = distance[i][k] + distance[k][j];
                        path[i][j] = path[k][j];
                    }
                
                }
            }
        }
   }

std::list<Nodo> Citta::print_path(Nodo source, Nodo destination){

    std::list<Nodo> optimal_path = std::list<Nodo>();
    

    if (source.nome() >= n_righe*n_colonne || destination.nome() >= n_righe*n_colonne){
        return optimal_path;    
    }

    if (path[source.nome()][destination.nome()].nome() == -1){
        return optimal_path;
    }

    optimal_path.push_front(destination);

    while(path[source.nome()][destination.nome()].nome() != source.nome()){
        optimal_path.push_back(path[source.nome()][destination.nome()]);        
        destination = path[source.nome()][destination.nome()];
    }
    return optimal_path;
}

Citta::Citta() {}

Citta::Citta(short righe, short colonne, float probabilita_senso_unico):n_righe(righe), n_colonne(colonne)
{ 

    matrice_adiacenza = new Strada*[n_righe*n_colonne];
    path = new Nodo*[n_righe*n_colonne];
    distance = new int*[n_righe*n_colonne];
    insieme_nodi = new Nodo[n_righe*n_colonne];
    for( int i = 0; i < n_righe*n_colonne; i++)
    {
        matrice_adiacenza[i] = new Strada[n_righe*n_colonne];
        path[i] = new Nodo[n_righe*n_colonne];
        distance[i] = new int[n_righe*n_colonne];
    }

    srand(time(NULL));
    std::string elenco = "{'lista':[";

    for (int i = 0; i < n_righe*n_colonne; i++ ){
        matrice_adiacenza[i][i] = Strada(-1);
        for (int j = i+1; j < n_righe*n_colonne; j++){              
            float r = rand();
            if ((j == i+1 && j%n_colonne != 0) || j == i+n_colonne ){
                matrice_adiacenza[i][j] = Strada(0);
                if (r/RAND_MAX > probabilita_senso_unico){
                    matrice_adiacenza[j][i] = Strada(0);
                } else {
                    matrice_adiacenza[j][i] = Strada(-1);
                    elenco.append("[");
                    elenco.append(std::to_string(i));
                    elenco.append(",");
                    elenco.append(std::to_string(j));
                    elenco.append("],"); 
                    //lista = {"lista": [  [1,2], [2,3], [3,4]  ]}           

                }
            } else {
                matrice_adiacenza[i][j] = Strada(-1);
                matrice_adiacenza[j][i] = Strada(-1);
            }
            std::cout << matrice_adiacenza[i][j].lunghezza() << std::endl;
        }
    }
    elenco.pop_back();
    elenco.append("]}"); 
  
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