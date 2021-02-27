

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "car.h"
#include "city.h"
#include "node.h"
#include <list>
#include <time.h>
#include <iostream>
#include<vector>
#include<algorithm>
#include <iterator>

#define N_CARS 100

struct Car_Info
{
    std::list<Node> path;
    Node position;
    Car* car;
    Car_Info(): path(std::list<Node>()), position(Node()), car(new Car()){}
};

class Simulator
{
    std::vector<Car_Info> _car_vector;
    short _cars_at_destination = 0;
    City _city;
    inline Node _find_next(int car_index)const;
    inline Road _find_road(int car_index)const;
  public:
    void _mv_car(int car_index); //TODO refractor
    Simulator();      
    void create_city(short n_rows, short n_coloumns, float oneway_fraction);
    void create_path();
    float traffic();
    City get_city()const;
    short get_cars_at_destination();
    std::vector<Car_Info> get_car_vector();
};

#endif