#ifndef CAR_H
#define CAR_H

struct position
{
    road r; 
    // road è la classe strada che per esempio è tra i vertici u e w
    // equivalente alla coppia ORDINATA (u,w)
    double t; 
    // La posizione del segmento [u,w] è (1-t)*u+t*w
    // dobbiamo implementare una classe di vettori di R^2(u e w sono vettori)
    // io userei std::vector per pigrizia
};

class car
{
        double l;
	// Lungezza dell'auto
	double v; 
	// Velocità
	position p; 
	// Posizione nel reticolo
	position origin;
	// Origine dell'auto
	position destination;
	// Destinazione dell'auto
	std::vector<road> path;
	// Algoritmo di minimizzazione dei tempi di percorrenza
    public:
        double get_v()const;
	double get_p()const;
	position get_origin()const;
	position get_destination()const
	std::vector<road> get_path()const;

};


#endif
