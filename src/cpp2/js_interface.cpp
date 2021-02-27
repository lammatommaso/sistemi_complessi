#include <node_api.h>

#include <node.h>
#include <assert.h>
#include <stdio.h>
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
//using namespace Dio;

using json = nlohmann::json;

bool _order(Car_Info i, Car_Info j)
{
    return (i.car->get_offset() > j.car->get_offset());
}

napi_value myMain(napi_env env, napi_callback_info info){
    napi_status status;

    Simulator dio = Simulator();
    cout << "Inizio a creare la città...\n";
    dio.create_city(30,30,0.3);
    cout << "fatto. Creo i percorsi...\n";
    dio.create_path();
    cout << "fatto\n";

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

    int counter = 0;

    while (dio.get_cars_at_destination() < N_CARS)
    {        
        std::vector<Car_Info>::iterator end = dio.get_car_vector().begin();
        std::advance(end, dio.get_car_vector().size() - 1);
        sort(dio.get_car_vector().begin(), end, _order);
               
        for (int i = 0; i < N_CARS; i++)
        { 
            if (!(dio.get_car_vector()[i].car->get_at_destination()) && dio.get_car_vector()[i].car->get_delay() == 0)
            {
                dio._mv_car(i);

            }
            else
            {   
                dio.get_car_vector()[i].car->delay();
            }
        }  

        napi_value argv[1];
        json j = {{"callback", "while"}}; //FIXME
        status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
        
        napi_value result;
        cout << "chiamo la callback...\n";
        napi_call_function(env, global, cb, 1, argv, &result);
        assert(status == napi_ok);
                
        counter++;
    }

    cout << "Uscita dal while\n";

    float steps_mean = 0;
    for (int i = 0; i < N_CARS; i++)
    {
        steps_mean += dio.get_car_vector()[i].car->get_steps();
    }


    //chiama la callback 
    
    /*napi_value argv[1];
    json j = {"ciao", "mondo"}; //FIXME
    status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    napi_value result;
    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);*/

    napi_value argv[1];
    json j = {{"callback", "finale"}}; //FIXME
    status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    
    napi_value result;

    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);

    return nullptr;
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
    //status = napi_create_string_utf8(env, dio.get_citta().elenco.c_str(), NAPI_AUTO_LENGTH, &grf);
    status = napi_create_string_utf8(env, "ciao", NAPI_AUTO_LENGTH, &grf);
    if (status != napi_ok) return nullptr;
    return grf;

}
//disegna roba deve restituirci la posizione delle machhine
//per ogni macchina mi dice dov'è la macchina in quel momento
//chiamo la callback restituendo l'array
//lo faccio ogni volta che si sono mosse tutte le macchine


napi_value init(napi_env env, napi_value exports) {
    napi_status status;

    napi_value fn1;

    status = napi_create_function(env, nullptr, 0, pulisci_archi, nullptr, &fn1);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "pulisci_archi", fn1);
    if (status != napi_ok) return nullptr;

    napi_value fn2;

    status = napi_create_function(env, nullptr, 0, avvisami_quando_disegnare, nullptr, &fn2);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "avvisami_quando_disegnare", fn2);
    if (status != napi_ok) return nullptr;

    napi_value fn3;

    status = napi_create_function(env, nullptr, 0, myMain, nullptr, &fn3);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "mymain", fn3);
    if (status != napi_ok) return nullptr;

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)