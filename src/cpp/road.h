#ifndef ROAD_H
#define ROAD_H
#include"car.h"

class road
{
        node _A;
	//Inizio della strada
        node _B;
	//Fine della strada
	short _N;
	//Numero massimo di auto nella strada
	double _time[_N];
	//Auto in transito nella strada in ordine di arrivo
	short _n=0;
	//Numero di auto presenti nella strada
	bool _oneway;
    public:
        road(node A,node B,bool oneway);
	//Costruttore di default
	//Riempie l'array con N zeri e n=0
        void add_car();
	//Aggiunge un tempo all'array a 0
	//n++
	//Tutti i tempi nell'array fino ad n sono incrementati di continuo 
	bool is_full()const;
	//true se n=N
	double get_time()const;
	//Media i tempi dell'array con una distibuzione 
	//pesata maggiormente sugli ultimi che hanno lasciato la strada
};






#endif
