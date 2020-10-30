#ifndef ADJ_H
#define ADJ_H

// La matrice di adiacenza del grafo associato ad un reticolo n*m
// è a[i][j]=1(j>i) se j-i=m e se j-i=1, 0 altrimenti, poi è simmetrica
// escludendo sensi unici con diagonale di zeri

class city
{
        static const int n = 50, m = 50; //limite massimo! non superare!
        /*il prodotto non deve superare 1444 (quindi per es. 14*100 va bene) */
        bool adj[n*m][n*m];
    public:
        city(float p);

};

#endif
