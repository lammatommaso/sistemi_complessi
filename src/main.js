//const { worker } = require("cluster");

const { ADDRCONFIG } = require("dns");
const electron = require("electron");
const app = electron.app // require('app');
const BrowserWindow = electron.BrowserWindow // require('browser-window')
const ipcMain = electron.ipcMain //require("ipcMain")

// const { app, BrowserWindow, ipcMain } = require("electron")
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
})


const { Worker, workerData, parentPort } = require('worker_threads')

ipcMain.on("batch_init", (event, base_dir_s, simulation_type, 
        p, cols, rows, min_car, max_car, increment, 
        car_number, gaussian_mean, gaussian_sigma, min_road_length, 
        max_road_length) => {
        const prom = new Promise((resolve, reject) => {
            w = new Worker('./javascript/serviceBatch.js', {workerData: {"base_dir": base_dir_s, "simulation_type": simulation_type, 
                "p": p, "cols": cols, "rows": rows, "min_car": min_car, "max_car": max_car, "increment": increment, 
                "n_cars": car_number, "gaussian_mean": gaussian_mean, "gaussian_sigma": gaussian_sigma, "min_road_l": min_road_length, 
                "max_road_l": max_road_length, "str_len": base_dir_s.length + 1}} );
            //w.on('message', resolve);
            w.on('error', reject);
            w.on('exit', (code) => {
            if (code !== 0)
                reject(new Error(`Worker stopped with exit code ${code}`));
            })
            
            console.log("Thread creato")
            
            w.addListener("message", (data)=>{
                console.log("Ricevuto messaggio da thread simulazione")
                console.log(data)
                //event.reply(data["name"], data["data"])
            })
    
        });
    
        prom.then(() => {
            console.log("finito")
        })

})
 
ipcMain.on("init", (event, increment, n_cars,  rows, columns,   gaussian_mean, gaussian_sigma, min_road_l, max_road_l) => {
    
    const prom = new Promise((resolve, reject) => {
        w = new Worker('./javascript/service.js', {workerData: {"increment": increment, "n_cars": n_cars, "rows": rows, 
        "columns": columns, "gaussian_mean": gaussian_mean, "gaussian_sigma": gaussian_sigma, 
            "min_road_l": min_road_l, "max_road_l": max_road_l}} );
        //w.on('message', resolve);
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

ipcMain.on("next", (event) => {
    w.postMessage({"name": "next"})
})

ipcMain.on("create_path", (event, s1, s2) => {
    //s1 è il primo insieme => insieme dei nodi di partenza
    //s2 è il secondo insieme => insieme dei nodi di arrivo
    w.postMessage({"name": "create_path", "data": {"l1": s1.length, "l2": s2.length, "s1": s1, "s2": s2}})
})

ipcMain.on("start_simulation", (event) => {
    w.postMessage({"name": "start_simulation"})
})