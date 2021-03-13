#ifndef BATCH_SIMULATION
#define BATCH_SIMULATION

#include<iostream>
#include<thread>
#include<string>
#include<chrono>
#include"simulator.h"

#define ONEWAY_INCREMENT_SIMULATION 0
#define CAR_INCREMENT_SIMULATION 1

class Batch_Simulation {
    private:
        void _car_increment_simulation(int city_number, std::string sim_dir, short min_car_number, short max_car_number, short increment, float oneway_fraction, short n_rows, short n_coloumns);
        void _oneway_increment_simulation(std::string sim_dir,float increment, short car_number, short n_rows, short n_coloumns);
    public:
        Batch_Simulation(std::string base_dir, int simulation_type, 
                                        float p, int cols, int rows, int min_car, int max_car, int increment, 
                                        int car_number, int gaussian_mean, int gaussian_sigma, int min_road_length, 
                                        int max_road_length);  
};

#endif