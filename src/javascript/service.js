const { workerData, parentPort } = require('worker_threads')

const addon = require('../build/Release/addon');

addon.mymain(workerData["increment"], workerData["n_cars"],  workerData["rows"], workerData["columns"], workerData["gaussian_mean"], 
    workerData["gaussian_sigma"], workerData["min_road_l"], workerData["max_road_l"], (grafo) => {
      parentPort.postMessage({"name": "grafo", "data": grafo})
    
});

parentPort.on("message", (data) => {
    console.debug("Nuovo messaggio da main")
    if (data["name"] == "create_path"){
        console.debug("Creiamo la path")
        addon.create_path(data["data"]["l1"], data["data"]["l2"], data["data"]["s1"], data["data"]["s2"]);
    }
    else if (data["name"] == "start_simulation"){
        console.debug("Iniziamo la simulazione")
        addon.start_simulation((stringa) => {
        
            parentPort.postMessage({"name": "disegnami", "data": stringa})
            
        });
    }
})
