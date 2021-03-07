const { workerData, parentPort } = require('worker_threads')

const addon = require('../build/Release/addon');



console.log("Avvio thread simulazione...")

addon.mymain( workerData["rows"], workerData["columns"], workerData["n_cars"], workerData["increment"], workerData["gaussian_mean"], 
    workerData["gaussian_sigma"], workerData["min_road_l"], workerData["max_road_l"], (grafo) => {
    
    console.log("grafo creato, lo inviamo alla grafica perché lo disegni...")
    //console.debug(grafo)
    parentPort.postMessage({"name": "grafo", "data": grafo})
    
});

console.log("funzione mymain chiamata")

parentPort.on("message", (data) => {
    console.debug("Nuovo messaggio da main")
    if (data["name"] == "create_path"){
        console.debug("Creiamo la path")
        addon.create_path(data["data"]["l1"], data["data"]["l2"], data["data"]["s1"], data["data"]["s2"]);
    }
    else if (data["name"] == "start_simulation"){
        console.debug("Iniziamo la simulazione")
        addon.start_simulation((stringa) => {
            console.log("Nuovo dato da disegnare");
            //console.debug(stringa)
        
            parentPort.postMessage({"name": "disegnami", "data": stringa})
            //if (workerData)
            //    workerData.reply("disegnami", stringa)
            
        });
    }
})

console.log("Fine thread simulazione")