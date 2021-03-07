#include"road.h"

Road::Road() : _car_number(0)
{
    std::random_device generator;
    std::normal_distribution<double> gaussian(GAUSSIAN_MEAN,GAUSSIAN_SIGMA);
    do
    {
        _road_length = (short)gaussian(generator);
    }
    while(_road_length <= MIN_ROAD_LENGTH || _road_length > MAX_ROAD_LENGTH);
}  
Road::Road(short car_number) : _car_number(car_number)
{
    std::random_device generator;
    std::normal_distribution<double> gaussian(GAUSSIAN_MEAN,GAUSSIAN_SIGMA);
    do
    {
        _road_length = (short)gaussian(generator);
    }
    while(_road_length <= MIN_ROAD_LENGTH || _road_length > MAX_ROAD_LENGTH);
}
Road::Road(Road const& Road) : _car_number(Road._car_number), _road_length(Road._road_length){}
short Road::get_car_number() const { return _car_number; }
short Road::get_road_length(){return _road_length;}
void Road::add_car() { _car_number++; }
void Road::rm_car() { _car_number--; }
