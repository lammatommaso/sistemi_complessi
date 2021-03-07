
#include<iostream>
#include<thread>
#include<string>
#include<chrono>
#include"simulator.h"

void oneway_increment_simulation(std::string sim_dir, float increment, short car_number, short n_rows, short n_coloumns, short gaussian_mean, short gaussian_sigma, short min_road_length, short max_road_length)
{
   std::vector<float> x;
   std::vector<float> mean_steps;
   std::vector<float> sigma_steps;
   std::vector<float> mean_stops;
   std::vector<float> sigma_stops;
   auto start = std::chrono::steady_clock::now();
   short city_number = 1;
   for(float i=0; i<1; i+=increment)
   {
      Simulator simulator(car_number);
      simulator.create_city(n_rows,n_coloumns,i,gaussian_mean,gaussian_sigma,min_road_length,max_road_length);
      simulator.create_path();
      simulator.simulation();

      std::ofstream citydata;
      citydata.open(sim_dir+"/city/citydata"+std::to_string(city_number)+".py");
      citydata<<simulator.print();
      citydata.close();

      x.push_back(simulator.get_city().get_oneway_fraction());
      mean_steps.push_back(simulator.get_result().steps_mean);
      sigma_steps.push_back(simulator.get_result().steps_sigma);
      mean_stops.push_back(simulator.get_result().stops_mean);
      sigma_stops.push_back(simulator.get_result().stops_sigma);
      city_number++;
   }
   auto stop = std::chrono::steady_clock::now();
   std::chrono::duration<float> execution_time = stop-start;   
   std::ofstream simdata;
   simdata.open(sim_dir+"/simdata.py");
   simdata<<Numpy_Parser::numpy();
   simdata<<Numpy_Parser::print_array("x", x)
           <<Numpy_Parser::print_array("mean_steps", mean_steps)
           <<Numpy_Parser::print_array("sigma_steps", sigma_steps)
           <<Numpy_Parser::print_array("mean_stops", mean_stops)
           <<Numpy_Parser::print_array("sigma_stops", sigma_stops)
           <<Numpy_Parser::print_var("execution_time", execution_time.count());
   simdata.close();
}

int main()
{
   for(short car_number=2000; car_number<=2000; car_number+=200)
   {
      std::string sim_dir = "../simulation/oneway_increment_simulation/" + std::to_string(car_number);
      oneway_increment_simulation(sim_dir,0.005, car_number, 10, 10, 20, 10, 5, 30);
   }
   return 0;
}
