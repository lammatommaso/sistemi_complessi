const { workerData, parentPort } = require('worker_threads')

const addon = require('../build/Debug/addon');

addon.mymain(workerData["increment"], workerData["n_cars"],  workerData["rows"], workerData["columns"], workerData["gaussian_mean"], 
    workerData["gaussian_sigma"], workerData["min_road_l"], workerData["max_road_l"], (grafo) => {
      parentPort.postMessage({"name": "grafo", "data": grafo})
    
});

parentPort.on("message", (data) => {
    if (data["name"] == "create_path"){
        addon.create_path(data["data"]["l1"], data["data"]["l2"], data["data"]["s1"], data["data"]["s2"]);
    }
    else if (data["name"] == "start_simulation"){

        addon.start_simulation((stringa) => {
        
            parentPort.postMessage({"name": "disegnami", "data": JSON.parse(stringa)})
            
            
        });
    }
})
