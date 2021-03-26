const { workerData, parentPort } = require('worker_threads')

const addon = require('../build/Debug/addon');

// ONEWAY_INCREMENT_SIMULATION 0
// CAR_INCREMENT_SIMULATION 1

addon.batchmain(workerData["base_dir"], workerData["simulation_type"], workerData["p"],  workerData["cols"], workerData["rows"], 
    workerData["min_car"], workerData["max_car"], workerData["increment"], workerData["n_cars"], workerData["gaussian_mean"], 
    workerData["gaussian_sigma"], workerData["min_road_l"], workerData["max_road_l"], workerData["str_len"], (msg) => {
      parentPort.postMessage({"name": "batch_simulation_end", "data": msg})
    
});

