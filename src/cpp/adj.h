#ifndef ADJ_H
#define ADJ_H

// La matrice di adiacenza del grafo associato ad un reticolo n*m
// è a[i][j]=1(j>i) se j-i=m e se j-i=1, 0 altrimenti, poi è simmetrica
// escludendo sensi unici con diagonale di zeri

class matrice_adiacenza {
    private:
        static const int n = 38, m = 38; //limite massimo! non superare!
        /*il prodotto non deve superare 1444 (quindi per es. 14*100 va bene) */
        
        int matrice[n*m][n*m];
    public:
        matrice_adiacenza(float parametro_magico);

};

#endif
