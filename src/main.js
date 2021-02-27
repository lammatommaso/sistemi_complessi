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
ipcMain.on("init", (event) => {

    const prom = new Promise((resolve, reject) => {
        const worker = new Worker('./javascript/service.js', "" );
        worker.on('message', resolve);
        worker.on('error', reject);
        worker.on('exit', (code) => {
        if (code !== 0)
            reject(new Error(`Worker stopped with exit code ${code}`));
        })

        worker.addListener("message", (data)=>{
            event.reply(data["name"], data["data"])
        })

    });

    prom.then(() => {
        console.log("finito")
    })


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