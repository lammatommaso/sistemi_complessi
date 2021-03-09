#include <node_api.h>

#include <node.h>
#include <assert.h>
//#include <stsim.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <list>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "simulator.h"
#include "road.h"
#include "car.h"



using namespace std;

using json = nlohmann::json;

bool _order(Car_Info i, Car_Info j)
{
    return (i.car->get_offset() > j.car->get_offset());
}

Simulator sim = NULL;

std::ofstream logFile("/home/simone/Scrivania/logfile.txt");


napi_value myMain(napi_env env, napi_callback_info info){
    napi_status status;


    //prendi parametri (callback, variabili...)
    size_t argc = 9;
    napi_value args[9];
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);

    int n_cars, rows, columns, gaussian_mean, gaussian_sigma, min_road_l, max_road_l ;
    double increment;

    status = napi_get_value_double(env, args[0], &increment);
    status = napi_get_value_int32(env, args[1], &n_cars);
    status = napi_get_value_int32(env, args[2], &rows);
    status = napi_get_value_int32(env, args[3], &columns);
    status = napi_get_value_int32(env, args[4], &gaussian_mean); 
    status = napi_get_value_int32(env, args[5], &gaussian_sigma); 
    status = napi_get_value_int32(env, args[6], &min_road_l); 
    status = napi_get_value_int32(env, args[7], &max_road_l);

    logFile << "Instanzio la simulazione\n";
    sim = Simulator(n_cars);
    logFile << "fatto\n";
    logFile.flush();
    
    sim.create_city(rows, columns, increment, gaussian_mean, gaussian_sigma, min_road_l, max_road_l);
    
    //gestione callback
    napi_value cb = args[8];
    napi_value global;
    status = napi_get_global(env, &global);
    assert(status == napi_ok);

    //grafo creato, lo invio alla grafica
    logFile << "Inizializzo dati callback\n";
    logFile.flush();
    napi_value argv[1];
    Road** r = sim.get_city().get_adj_matrix();
    logFile << "Strada scaricata\n";
    logFile.flush();
    json j = {};
    logFile << "Inizio conversione...\n";
    logFile.flush();
    for (int x = 0; x < sim.get_city().get_n_rows()*sim.get_city().get_n_coloumns(); x++){
        for (int y=0; y < sim.get_city().get_n_rows()*sim.get_city().get_n_coloumns(); y++){
            if (sim.get_city().get_road(x,y).get_car_number() >= 0)
                j.push_back({{"x", x}, {"y", y}});
                logFile << "Inserisco strada " << x << ", " << y << "\n";
                logFile.flush();
        }
    }
    logFile << "Conversione avvenuta\n";
    logFile.flush();

    json nodes = {{"nodes", j}};

    status = napi_create_string_latin1(env, nodes.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    
    napi_value result;

    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);


    cout << "Callback chiamata\n";

    return nullptr;
}

napi_value create_path(napi_env env, napi_callback_info info){
    napi_status status;

    logFile << "sono in create_path\n";
    logFile.flush();

    //prendi parametri (callback, variabili...)
    size_t argc = 4;
    napi_value args[4];
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);

    int start_lenght, end_lenght;
    status = napi_get_value_int32(env, args[0], &start_lenght);
    status = napi_get_value_int32(env, args[1], &end_lenght);

    int source_nodes[start_lenght], dest_nodes[end_lenght];
    napi_value e;
    int v;

    for (int i=0; i < start_lenght; i++){
        status = napi_get_element(env, args[2], i, &e);
        status = napi_get_value_int32(env, e, &v);
        source_nodes[i] = v;
    }

    for (int i=0; i < end_lenght; i++){
        status = napi_get_element(env, args[3], i, &e);
        status = napi_get_value_int32(env, e, &v);
        dest_nodes[i] = v;
    }

    sim.create_path(start_lenght, end_lenght, source_nodes, dest_nodes);

    return nullptr;
}

json get_updates(){
    json tmp = {};
    for (int i = 0; i < sim.get_city().get_n_rows()*sim.get_city().get_n_coloumns(); i++){
        for (int j = 0; j < sim.get_city().get_n_rows()*sim.get_city().get_n_coloumns(); j++){
            if (sim.get_city().get_road(i, j).get_car_number() >= 0){
                int max = sim.get_city().get_road(i, j).get_road_length();
                int cars = sim.get_city().get_road_ptr(i, j)->cars_in_road;
                //int cars = sim.get_city().get_road(i, j).get_car_number();

                tmp.push_back({{"street", {{"x", i}, {"y", j}}}, {"max", max}, {"cars", cars}});
            }
        }    
    }
    logFile.flush();

    return {{"streets", tmp}};
} 

napi_value start_simulation(napi_env env, napi_callback_info info){
    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);

    //gestione callback
    napi_value cb = args[0];
    napi_value global;
    status = napi_get_global(env, &global);
    assert(status == napi_ok);
    napi_value argv[1];
    
    int counter = 0;
    while (sim.get_cars_at_destination() < sim.get_car_number())
    {
        //std::sort(_car_vector.begin(), _car_vector.end(), order);

        std::vector<Car_Info>::iterator end = sim.get_car_vector().begin();
        std::advance(end, sim.get_car_vector().size() - 1);
        sort(sim.get_car_vector().begin(), end, _order);

        for (int i = 0; i < sim.get_car_number(); i++)
        { 
            if (!(sim.get_car(i).car->get_at_destination()) && sim.get_car(i).car->get_delay() == 0)
            {
                sim.mv_car(i);
            }
            else
            {
                sim.get_car(i).car->delay();
            }
        }  

        napi_value result;

        json j = get_updates();
        status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
        
        cout << "chiamo la callback...\n";
        napi_call_function(env, global, cb, 1, argv, &result);
        assert(status == napi_ok);

        counter++;
    }

   
    float steps_mean = 0;
    float steps_squared_mean = 0;
    float stops_mean = 0;
    float stops_squared_mean = 0;
    for (int i = 0; i < sim.get_car_number(); i++)
    {
        steps_mean += sim.get_car(i).car->get_steps();
        steps_squared_mean += pow(sim.get_car(i).car->get_steps(),2);
        stops_mean += sim.get_car(i).car->get_stops();
        stops_squared_mean += pow(sim.get_car(i).car->get_stops(),2);

    }

   

    steps_mean /= sim.get_car_number();
    steps_squared_mean /= sim.get_car_number();
    stops_mean /= sim.get_car_number();
    stops_squared_mean /= sim.get_car_number();

    

    Result r = sim.get_result();

    
    r.steps_mean = steps_mean;
    r.steps_sigma = sqrt(steps_squared_mean - pow(steps_mean,2));
    r.stops_mean = stops_mean;
    r.steps_sigma = sqrt(stops_squared_mean - pow(stops_mean,2));


    sim.set_result(r);


    return nullptr;
}


napi_value init(napi_env env, napi_value exports) {
    cout << "Inizializzo addon\n"; 

    napi_status status;

    napi_value fn1;

    status = napi_create_function(env, nullptr, 0, start_simulation, nullptr, &fn1);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "start_simulation", fn1);
    if (status != napi_ok) return nullptr;

    napi_value fn2;

    status = napi_create_function(env, nullptr, 0, create_path, nullptr, &fn2);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "create_path", fn2);
    if (status != napi_ok) return nullptr;

    napi_value fn3;

    status = napi_create_function(env, nullptr, 0, myMain, nullptr, &fn3);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "mymain", fn3);
    if (status != napi_ok) return nullptr;

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)