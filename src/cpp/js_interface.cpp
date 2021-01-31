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
#include "Citta.h"
#include "Macchina.h"

using namespace std;
//using namespace Dio;

using json = nlohmann::json;

Dio dio;
void _main(){
    std::cout<<"Inizio"<<"\n";
    //std::cout<<c.insieme_nodi[2].nome();

   //Macchina* macchine[N_MACCHINE];
   dio.crea_citta(3,3,0.5);
   cout << "Ho creato Città \n";
   dio.crea_percorso();
   cout << "Ho creato Percorso \n";
   //dio.avvia_macchine();

   //for (int i = 0; i < N_MACCHINE; i++){
   //   macchine[i] = new Macchina();
   //}

   
   /*while (_macchine_a_destinazione < N_MACCHINE){
      for (int i = 0; i < N_MACCHINE; i++){
         std::cout << "Muovo la macchina " << i << "\n"; 
         if (!(macchine[i]->destinazione_raggiunta)){
            muovi_macchina(macchine[i], i);
         }
      }  
   }*/
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

    Dio god;
    std::string elenco = "{'lista':[";
    /*[posattuale,posnext]*/
    for(int i = 0; i<N_MACCHINE; i++){
        elenco.append("[");
                elenco.append(std::to_string(god.pos_corrente(i).nome);
                elenco.append(",");
                elenco.append(std::to_string(god.trova_next(i).nome));
                elenco.append("],");

    }
        
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

}
//restituisce la martice di adiacenza come lista degli archi inesistenti, sotto forma di json o array di interi
napi_value pulisci_archi(napi_env env, napi_callback_info args){

    Citta city;
    int righe = city.n_righe;
    int colonne = city.n_colonne;
    std::string elenco = "{'lista':[";
    for(int i = 0; i < righe; i++){
        for(int j = 0; j< colonne; j++){
            if(city.matrice_adiacenza[i][j]== /*vuota*/){
                elenco.append("[");
                elenco.append(std::to_string(i));
                elenco.append(",");
                elenco.append(std::to_string(j));
                elenco.append("],"); 
            }
        }
    }
    elenco.pop_back();
    elenco.append("]}"); 

    /*json valore_da_restituire = {{"chiave", "valore"}, {"chiave2","valore2"}};
    napi_value grf;
    napi_status status;

    //status = napi_create_string_utf8(env, valore_da_restituire.dump().c_str(), NAPI_AUTO_LENGTH, &grf);
    status = napi_create_string_utf8(env, dio.get_citta().elenco.c_str(), NAPI_AUTO_LENGTH, &grf);
    if (status != napi_ok) return nullptr;
    return grf;*/

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