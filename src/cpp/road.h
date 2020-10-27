#ifndef ROAD_H
#define ROAD_H
#include"car.h"

class road
{
        node A;
	//Inizio della strada
        node B;
	//Fine della strada
	short N;
	//Numero massimo di auto nella strada
	double time;
	//Auto in transito nella strada in ordine di arrivo
	short n;
	//Numero di auto presenti nella strada
	
        //Magari mediato con una distribuzione che non riesco a disegnare
    public:
        void add_car();
	//Aggiunge un tempo all'array a 0
	//n++
	//Tutti i tempi nell'array fino ad n sono incrementati di continuo 
};






#endif
