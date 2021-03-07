
#include <iostream>
#include <thread>
#include "simulator.h"

void foo(){
   Simulator dio;
   dio.create_city(30,30,0.3);
   dio.create_path();
   float mean_steps = dio.traffic();
   std::cout<<mean_steps<<std::endl;
}

int main()
{
  std::thread first(foo);     
  std::thread second(foo); 
  std::thread third(foo);
  first.join();               
  second.join();  
  third.join();
}

