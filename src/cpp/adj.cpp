#include "adj.h"
#include <cmath>
#include <time.h>
#include <iostream>

using namespace std;

matrice_adiacenza::matrice_adiacenza(float parametro_magico){

    srand(time(NULL));

    /*for (int i = 0; i < n*m; i++){
        for (int j = 0; j < n*m; j++){
            matrice[i][j] = 0;
        }
    }*/

    //float choice = rand();///RAND_MAX; // % 100; //genera numeri da 0 a 99
    //cout << "choice: " << choice << "\n";
    float uni_sopra=0, uni_sotto=0;

    for (int i = 0; i < n*m; i++ ){
        matrice[i][i] = 0;
        for (int j = i+1; j < n*m; j++){
              
            float choice = rand();///(RAND_MAX); // % 100; //genera numeri da 0 a 99
            //cout << "rand: " << (int)choice << " RAND_MAX: " << RAND_MAX << "\n";
            if ((j == i+1 && j%n != 0) || j == i+n ){
                matrice[i][j] = 1;
                uni_sopra++;
                if (choice/RAND_MAX > parametro_magico){
                    matrice[j][i] = 1;
                    uni_sotto++;
                } else {
                    matrice[j][i] = 0;
                    
                }
            } else {
                matrice[i][j] = 0;
                matrice[j][i] = 0;
            }

            

            /*

            if(j < m && i < n){
                matrice[i][j] = 1;
                if (i < m && j < n){
                matrice[j][i] = 1;
            }
            }

            

            if (i+n < m){
                matrice[i][i+n] = 1;
            }

            break;
            */

            /*if (j == i+1 || i == j+1){
                matrice[i][j] == 1;                
            } else {
                matrice[i][j] == 0;
            }*/
        }
    }

    cout << "uni_sotto/uni_sopra " << (uni_sotto/uni_sopra) << "\n"; 

    /*for (int i = 0; i < n*m; i++){
        for (int j = 0; j < n*m; j++){
            cout << matrice[i][j] << " " ;
        }
        cout << "\n" ;
    }*/

    

};

class Lista_righe{
    int riga[100];
    Lista_righe *l;
};

int main(){
    matrice_adiacenza m = matrice_adiacenza(0.5);
}

