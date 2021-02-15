#include "simulator.h"
//using namespace Simulator;

bool order(Car_Info i, Car_Info j)
{
    return (i.car->get_offset() > j.car->get_offset());
}

    
Simulator::Simulator()
{
    for (int i = 0; i < N_CARS; i++)
    {
        _car_vector.push_back(Car_Info());
    }
}

void Simulator::create_city(short n_rows, short n_coloumns, float oneway_fraction)
{
    _city = City(n_rows, n_coloumns, oneway_fraction);
    /*for(int i=0;i<_city.get_n_rows()*_city.get_n_coloumns();i++)
    {
        for(int j=0;j<_city.get_n_rows()*_city.get_n_coloumns();j++)
        {
            if(_city.get_distance(i,j) < _city.get_n_rows()*_city.get_n_coloumns()*MAX_ROAD_LENGTH)
            {
                std::cout<<_city.get_distance(i,j)<<' ';
            }
            else
            {
                std::cout<<"+inf"<<' ';
            }
        }
        std::cout<<std::endl;
    }*/
}

Road Simulator::_find_road(int car_index)const
{     
    return _city.get_road(_car_vector[car_index].position.get_index(),_find_next(car_index).get_index());
}

Node Simulator::_find_next(int car_index)const
{
    bool search_end = false;
    Node next_node;
    for (Node n : _car_vector[car_index].path)
    {
        next_node = n;    
        if(search_end)
        {
            break;
        }
        if(n.get_index() == _car_vector[car_index].position.get_index())
        {
            search_end = true;
        } 
    }
    return next_node;
}

void Simulator::_mv_car(int car_index)
{
    Node next_node = _find_next(car_index);
    if(_car_vector[car_index].car->get_offset()<_find_road(car_index).get_road_length())
    {                
        bool can_move = 1;
        for(int i=0;i<N_CARS;i++)
        {
            if(_car_vector[car_index].position.get_index() == _car_vector[i].position.get_index() &&  _find_next(car_index).get_index() == _find_next(i).get_index())
            {
                can_move = _car_vector[car_index].car->get_offset() != _car_vector[i].car->get_offset() - 1;
                if(can_move == 0) break;
            }
        }
        if(can_move)
        {
            _car_vector[car_index].car->move_forward();
        }
        else
        {
            //std::cout<<"Non mi muovo"<<"\n";
        }
    }
    else
    {            
        _car_vector[car_index].position = next_node;
        _car_vector[car_index].car->move_forward();
        _car_vector[car_index].car->reset_offset();
    }
    if (_car_vector[car_index].position.get_index() ==  _car_vector[car_index].path.back().get_index())
    {
        _cars_at_destination++;
        _car_vector[car_index].car->set_at_destination(true);
    }
}

void Simulator::create_path()
{
    srand(time(NULL)); 
    for (int i = 0; i < N_CARS; i++)
    {
        Node source, destination;
        do
        {
            source = _city.get_node(rand()%(_city.get_n_rows()*_city.get_n_coloumns()));
            destination = _city.get_node(rand()%(_city.get_n_rows()*_city.get_n_coloumns()));
        }
        while(source.get_index() == destination.get_index() || _city.get_path(source.get_index(),destination.get_index()).get_index() == -1);
        //std::cout << source.get_index() << ' ' << destination.get_index() << std::endl;
        _car_vector[i].position = source;
        _car_vector[i].path = _city.print_path(source, destination); //nel path manca il nodo sorgente!
        _car_vector[i].path.push_front(source);

        /*for (auto it=_car_vector[i].path.begin(); it!=_car_vector[i].path.end(); ++it)
             std::cout << ' ' << (*it).get_index();
        std::cout << std::endl;*/
    }
}

float Simulator::traffic()
{
    int counter = 0;
    while (_cars_at_destination < N_CARS)
    {
        std::sort(_car_vector.begin(), _car_vector.end(), order);
        for (int i = 0; i < N_CARS; i++)
        { 
            if (!(_car_vector[i].car->get_at_destination()) && _car_vector[i].car->get_delay() == 0)
            {
                _mv_car(i);
            }
            else
            {
                _car_vector[i].car->delay();
            }
        }  
        counter++;
    }
    float steps_mean = 0;
    for (int i = 0; i < N_CARS; i++)
    {
        steps_mean += _car_vector[i].car->get_steps();
    }
    return steps_mean/N_CARS;
    //return (float)counter;
}

    

