#ifndef ROAD_H
#define ROAD_H

#include<random>

#define GAUSSIAN_MEAN 20
#define GAUSSIAN_SIGMA 10
#define MIN_ROAD_LENGTH 5
#define MAX_ROAD_LENGTH 30

class Road 
{
    short _car_number; 
    short _road_length;
  public:
    Road();
    Road(short car_number);
    Road(Road const& Road);
    short get_car_number()const;
    short get_road_length();
    void add_car();
    void rm_car();
};

#endif