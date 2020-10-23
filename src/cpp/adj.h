#ifndef ADJ_H
#define ADJ_H

// La matrice di adiacenza del grafo associato ad un reticolo n*m
// è a[i][j]=1(j>i) se j-i=m e se j-i=1, 0 altrimenti, poi è simmetrica
// escludendo sensi unici con diagonale di zeri

class matrice_adiacenza {
    private:
        
        int* matrice;
    public:
        matrice_adiacenza(int dimensione_x, int dimensione_y);

};

#endif
