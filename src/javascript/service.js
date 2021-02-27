const { workerData, parentPort } = require('worker_threads')

const addon = require('../build/Release/addon');

addon.avvisami_quando_disegnare( (stringa) => {
    console.log("avvisami quando disegnare: " + stringa);

    parentPort.postMessage({"name": "disegnami", "data": stringa})
    //if (workerData)
    //    workerData.reply("disegnami", stringa)
    
});

addon.mymain( (stringa) => {
    grafo = addon.pulisci_archi()
    
    parentPort.postMessage({"name": "grafo", "data": stringa})
    //if (workerData)
    //    workerData.reply("grafo", grafo)

    console.log("myMain: " + stringa)

    /*addon.avvisami_quando_disegnare( (stringa) => {
        console.log(stringa);
        event.reply("disegnami", stringa)
    });*/
});    