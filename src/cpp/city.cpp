#include "city.h"
#include <cmath>
#include <time.h>
#include <iostream>

city::city(float p){

    srand(time(NULL));

    float uni_sopra=0, uni_sotto=0;

    for (int i = 0; i < n*m; i++ ){
        adj[i][i] = 0;
        for (int j = i+1; j < n*m; j++){              
            float r = rand();
            if ((j == i+1 && j%n != 0) || j == i+n ){
                adj[i][j] = 1;
                uni_sopra++;
                if (r/RAND_MAX > p){
                    adj[j][i] = 1;
                    uni_sotto++;
                } else {
                    adj[j][i] = 0;
                    
                }
            } else {
                adj[i][j] = 0;
                adj[j][i] = 0;
            }
        }
    }

    std::cout << "uni_sotto/uni_sopra " << (uni_sotto/uni_sopra) << "\n";
}

int main(){
    city c(0.3);
}

