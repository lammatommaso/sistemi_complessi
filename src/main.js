const { worker } = require("cluster");
const { app, BrowserWindow, ipcMain } = require("electron")
const fs = require('fs');
const { on } = require("process");

var mainWindow = BrowserWindow

function createWindow() {
    mainWindow = new BrowserWindow({
        height: 600,
        width: 800,
        webPreferences: {
            nodeIntegration: true
        }
    })

    mainWindow.loadFile('html/index.html')

    mainWindow.on('closed', () => {
        app.quit()
    })

}

app.whenReady().then( () => {
    createWindow()

    /*********************** TEST addon c++ *****************************************************
    const addon = require('./build/Release/addon');
    addon.mymain( () => {
        console.log("ARCHI DA CANCELLARE:")
        console.log(addon.pulisci_archi()) 
        console.log("HO STAMPATO GLI ARCHI")
        

        addon.avvisami_quando_disegnare( (stringa) => {
            console.log(stringa);
        });
    });

    /********************************************************************************************/
})


const { Worker, workerData, parentPort } = require('worker_threads')
var w = ""
ipcMain.on("init", (event, rows, columns, n_cars, increment, gaussian_mean, gaussian_sigma, min_road_l, max_road_l) => {
    console.log(`min_road_l: ${min_road_l}, max_road_l: ${max_road_l}`)
    const prom = new Promise((resolve, reject) => {
        w = new Worker('./javascript/service.js', {workerData: {"rows": rows, "columns": columns, 
            "n_cars": n_cars, "increment": increment, "gaussian_mean": gaussian_mean, "gaussian_sigma": gaussian_sigma, 
            "min_road_l": min_road_l, "max_road_l": max_road_l}} );
        w.on('message', resolve);
        w.on('error', reject);
        w.on('exit', (code) => {
        if (code !== 0)
            reject(new Error(`Worker stopped with exit code ${code}`));
        })
        
        console.log("Thread creato")
        
        w.addListener("message", (data)=>{
            console.log("Ricevuto messaggio da thread simulazione")
            
            event.reply(data["name"], data["data"])
        })

    });

    prom.then(() => {
        console.log("finito")
    })
})

ipcMain.on("create_path", (event, s1, s2) => {
    //s1 è il primo insieme => insieme dei nodi di partenza
    //s2 è il secondo insieme => insieme dei nodi di arrivo
    w.postMessage({"name": "create_path", "data": {"l1": s1.length, "l2": s2.length, "s1": s1, "s2": s2}})
})

ipcMain.on("start_simulation", (event) => {
    w.postMessage({"name": "start_simulation"})
})

/*ipcMain.on("load_map", (event) => {
    fs.readFile('/home/simone/Scrivania/fisica/test.geojson', 'utf8', function (err,data) {
        if (err) {
          return console.log(err);
        }
        try {
            var parsed = JSON.parse(data)
            event.reply("load_map", parsed)
        } catch (exc){
            console.error(exc)
        }
      });
})*/