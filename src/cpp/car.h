#ifndef CAR_H
#define CAR_H
#include"node.h"

class car
{
	node origin;
	// Origine dell'auto
	node estination;
	// Destinazione dell'auto
	std::vector<node> path;
	// Algoritmo di minimizzazione dei tempi di percorrenza
    public:
	double get_p()const;
	position get_origin()const;
	position get_destination()const
	std::vector<road> get_path()const;

}; 
//Questa classe non serve e crea problemi di ereditarietà
//Delegherei il percorso da fare alla classe city, tanto si tratta solo di generare percorsi


#endif
