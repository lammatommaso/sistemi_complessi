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

    /*********************** TEST addon c++ *****************************************************/
    const addon = require('./build/Release/addon');
    addon.mymain( () => {
        console.log(addon.grafo()) 
        

        addon.avvisami_quando_disegnare( (stringa) => {
            console.log(stringa);
        });
    });

    /********************************************************************************************/
})

ipcMain.on("init", (event) => {
    const addon = require('./build/Release/addon');
    addon.mymain( () => {
        grafo = addon.grafo()
        
        event.reply("grafo", grafo)

        addon.avvisami_quando_disegnare( (stringa) => {
            console.log(stringa);
            event.reply("disegnami", questo)
        });
    });    
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