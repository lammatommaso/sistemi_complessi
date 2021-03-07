#ifndef SIMULATOR_H
#define SIMULATOR_H

#include"car.h"
#include"city.h"
#include"node.h"
#include<list>
#include<time.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iterator>
#include"numpy_parser.h"

struct Car_Info
{
    std::list<Node> path;
    Node position;
    Car* car;
    Car_Info();
};

struct Result
{
    float steps_mean;
    float steps_sigma;
    float stops_mean;
    float stops_sigma;
    Result();
    friend std::ostream& operator<<(std::ostream& output, const Result& result);
    friend std::istream& operator>>(std::istream& input, Result& result);

    float set_steps_mean(float s);
    float set_steps_sigma(float s);
    float set_stops_mean(float s);
    float set_stops_sigma(float s);
    
};

class Simulator
{
    std::vector<Car_Info> _car_vector;
    Result _result;
    short _cars_at_destination = 0;
    City _city;
    short _car_number;
    inline Node _find_next(int car_index)const;
    inline Road _find_road(int car_index)const;
    std::string print_car_data()const;
    std::string print_adj_matrix()const;
  public:
    Simulator(short car_number);      
    void create_city(int n_rows, int n_coloumns, float oneway_fraction, int gaussian_mean, int gaussian_sigma, int min_road_length, int max_road_length);
    void create_path();
    void simulation();
    City get_city()const;
    Result get_result()const;
    std::vector<Car_Info> get_car_vector()const;
    std::string print()const;

    void mv_car(int car_index);
    short get_cars_at_destination();
    short get_car_number();
    Car_Info get_car(int i);
    Result get_result();
    Result set_result(Result r);
};

#endif
