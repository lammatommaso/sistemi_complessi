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

#include "Dio.h"

using namespace std;
//using namespace Dio;

using json = nlohmann::json;

void _main(){
    std::cout<<"Inizio"<<"\n";
    //std::cout<<c.insieme_nodi[2].nome();

   Macchina* macchine[N_MACCHINE];

   crea_citta(0);
   crea_percorso();
   

   for (int i = 0; i < N_MACCHINE; i++){
      macchine[i] = new Macchina();
   }

   
   while (_macchine_a_destinazione < N_MACCHINE){
      for (int i = 0; i < N_MACCHINE; i++){
         std::cout << "Muovo la macchina " << i << "\n"; 
         if (!(macchine[i]->destinazione_raggiunta)){
            muovi_macchina(macchine[i], i);
         }
      }  
   }
}

napi_value myMain(napi_env env, napi_callback_info info){
    napi_status status;
    
    _main();

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
    json j = {}; //FIXME
    status = napi_create_string_latin1(env, j.dump().c_str(), NAPI_AUTO_LENGTH, argv);
    napi_value result;
    napi_call_function(env, global, cb, 1, argv, &result);
    assert(status == napi_ok);

    return nullptr;
}

napi_value avvisami_quando_disegnare(napi_env env, napi_callback_info info) {
        
    napi_status status;

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

    return nullptr;
}

napi_value grafo(napi_env env, napi_callback_info args){

    json valore_da_restituire = {{"chiave", "valore"}, {"chiave2","valore2"}};
    napi_value grf;
    napi_status status;
    json lista = {"lista": {}};

    j = {"lista": [1,2,3,4,5,6]}

    lista.push_back({{1, 2}})

    string s = "ciao";

    

    c.archi_cancellati

    status = napi_create_string_utf8(env, valore_da_restituire.dump().c_str(), NAPI_AUTO_LENGTH, &grf);
    if (status != napi_ok) return nullptr;
    return grf;

}

napi_value init(napi_env env, napi_value exports) {
    napi_status status;

    napi_value fn1;

    status = napi_create_function(env, nullptr, 0, grafo, nullptr, &fn1);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "grafo", fn1);
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