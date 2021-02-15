

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Car.h"
#include "City.h"
#include "Node.h"
#include <list>
#include <time.h>
#include <iostream>
#include<vector>
#include<algorithm>
#define N_CARS 100

struct Car_Info
{
    std::list<Node> path;
    Node position;
    Car* car;
};

class 
{ 
    std::vector<Car_Info> _car_vector;
    short _cars_at_destination = 0;
    City city;
    void mv_car(int car_index);
    inline Node _find_next(int car_index)const;
    inline Road _find_road(int car_index)const;
  public:
    Simulator();      
    void create_city(short n_rows, short n_coloumns, float oneway_fraction);
    void create_path();
    void start_traffic();
    City get_city()const;
};

#endif