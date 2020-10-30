const { app, BrowserWindow, ipcMain } = require("electron")
const fs = require('fs');

var mainWindow = BrowserWindow

function createWindow() {
    mainWindow = new BrowserWindow({
        height: 600,
        width: 800,
        webPreferences: {
            nodeIntegration: true
        }
    })

    mainWindow.loadFile('../html/index.html')

    mainWindow.on('closed', () => {
        app.quit()
    })

}

app.whenReady().then( () => {
    createWindow()

    /*********************** TEST addon c++ *****************************************************/
    //const addon = require('../build/Release/addon.node');
    //console.log(addon.hello()) //questo comando stampa word, ma il codice è in cpp/hello.cpp
    /********************************************************************************************/
})

ipcMain.on("load_map", (event) => {
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
})