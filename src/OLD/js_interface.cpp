#include <node_api.h>

#include <node.h>
#include <assert.h>
//#include <stsim.h>
#include <string.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <thread>
#include <list>
#include <filesystem>

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

napi_value myMain(napi_env env, napi_callback_info info){
    napi_status status;

    std::ofstream logFile("/home/simone/Scrivania/logfile.txt");

    //prendi parametri (callback, variabili...)
    size_t argc = 8;
    napi_value args[8];
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
    try {
        logFile << "Inizio a creare la città\n";
        logFile.flush();

        sim.create_city(rows, columns, 0.5, gaussian_mean, gaussian_sigma, min_road_l, max_road_l);
        logFile << "fatto\n";
        logFile.flush();

    } catch (const std::exception e){
        logFile << e.what() << "\n"; 
        logFile.flush();

    }
    
    //gestione callback
    napi_value cb = args[7];
    napi_value global;
    status = napi_get_global(env, &global);
    assert(status == napi_ok);

    //grafo creato, lo invio alla grafica
    napi_value argv[1];
    json j = {{"callback", "grafo"}}; //FIXME
    status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    
    napi_value result;

    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);


    cout << "Callback chiamata\n";
    
    /*int counter = 0;
    while (false && sim.get_cars_at_destination() < N_CARS) //TODO sposta in metodo start
    {        
        std::vector<Car_Info>::iterator end = sim.get_car_vector().begin();
        std::advance(end, sim.get_car_vector().size() - 1);
        sort(sim.get_car_vector().begin(), end, _order);
               
        for (int i = 0; i < N_CARS; i++)
        { 
            if (!(sim.get_car_vector()[i].car->get_at_destination()) && sim.get_car_vector()[i].car->get_delay() == 0)
            {
                sim._mv_car(i);

            }
            else
            {   
                sim.get_car_vector()[i].car->delay();
            }
        }  

        j = {{"callback", "while"}}; //FIXME
        status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
        
        cout << "chiamo la callback...\n";
        napi_call_function(env, global, cb, 1, argv, &result);
        assert(status == napi_ok);
                
        counter++;
    }

    cout << "Uscita dal while\n";

    float steps_mean = 0;
    for (int i = 0; i < N_CARS; i++)
    {
        steps_mean += sim.get_car_vector()[i].car->get_steps();
    }


    //chiama la callback 
    
    /*napi_value argv[1];
    json j = {"ciao", "mondo"}; //FIXME
    status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    napi_value result;
    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);
    

    j = {{"callback", "finale"}}; //FIXME
    status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    
    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);
    */
    
    return nullptr;
}

napi_value create_path(napi_env env, napi_callback_info info){
    napi_status status;

    //prendi parametri (callback, variabili...)
    size_t argc = 4;
    napi_value args[4];
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);

    int start_lenght, end_lenght;
    status = napi_get_value_int32(env, args[0], &start_lenght);
    status = napi_get_value_int32(env, args[1], &end_lenght);

    int start[start_lenght], end[end_lenght];
    napi_typedarray_type type;
    size_t st_l = start_lenght, end_l = end_lenght;
    napi_value out_start_l, out_end_l;
    void *data_start_l, *data_end_l; 
    status = napi_get_typedarray_info(env, args[2], &type, &st_l, &data_start_l, &out_end_l, 0);
    status = napi_get_typedarray_info(env, args[3], &type, &end_l, &data_end_l, &out_start_l, 0);
    
    sim.create_path(); //TODO passa quei valori

    return nullptr;
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

        json j = {{"callback", "while"}}; //FIXME
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
    r.set_steps_mean(steps_mean);
    r.set_steps_sigma(sqrt(steps_squared_mean - pow(steps_mean,2)));
    r.set_stops_mean(stops_mean);
    r.set_steps_sigma(sqrt(stops_squared_mean - pow(stops_mean,2)));
    sim.set_result(r);
}

napi_value avvisami_quando_disegnare(napi_env env, napi_callback_info info) {
        
    /*napi_status status;

    //prendi parametri (callback, variabili...)
    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);        

    //gestione callback
    napi_value cb = args[0];
    napi_value global;
    status = napi_get_global(env, &global);
    assert(status == napi_ok);

    //chiama la callback
    napi_value argv[1];
    json j = {{"chiave", "valore"}, {"chiave2","valore2"}};
    status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    napi_value result;
    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);

    return nullptr;*/

    napi_status status;

    size_t argc = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    assert(status == napi_ok);

    napi_value cb = args[0];

    napi_value argv[1];
    status = napi_create_string_utf8(env, "hello world", NAPI_AUTO_LENGTH, argv);
    assert(status == napi_ok);

    napi_value global;
    status = napi_get_global(env, &global);
    assert(status == napi_ok);

    napi_value result;
    status = napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);

    return nullptr;
}
//restituisce la martice di adiacenza come lista degli archi inesistenti, sotto forma di json o array di interi
napi_value pulisci_archi(napi_env env, napi_callback_info args){
   
    
    json valore_da_restituire = {{"chiave", "valore"}, {"chiave2","valore2"}};
    napi_value grf;
    napi_status status;

    //status = napi_create_string_utf8(env, valore_da_restituire.dump().c_str(), NAPI_AUTO_LENGTH, &grf);
    //status = napi_create_string_utf8(env, sim.get_citta().elenco.c_str(), NAPI_AUTO_LENGTH, &grf);
    status = napi_create_string_utf8(env, "ciao", NAPI_AUTO_LENGTH, &grf);
    if (status != napi_ok) return nullptr;
    return grf;

}
//disegna roba deve restituirci la posizione delle machhine
//per ogni macchina mi dice dov'è la macchina in quel momento
//chiamo la callback restituendo l'array
//lo faccio ogni volta che si sono mosse tutte le macchine


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