const { app, BrowserWindow } = require("electron")

var mainWindow = BrowserWindow

function createWindow() {
    mainWindow = new BrowserWindow({
        height: 600,
        width: 800
    })

    mainWindow.loadFile('../html/index.html')

    mainWindow.on('closed', () => {
        app.quit()
    })

}

app.whenReady().then( () => {
    createWindow()

    /*********************** TEST addon c++ *****************************************************/
    const addon = require('../build/Release/addon.node');
    console.log(addon.hello()) //questo comando stampa word, ma il codice è in cpp/hello.cpp
    /********************************************************************************************/
})

