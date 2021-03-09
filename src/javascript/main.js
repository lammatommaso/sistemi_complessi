const green  = "#9bee00"
const orange = "#ffaa00"
const red    = "#f00"

var s = new sigma({
renderer:{
    container: 'main', 
    type: 'canvas'
},
settings: {
    minArrowSize: 8,
    minEdgeSize: 8
}
})

function init(){
    const p      = document.getElementById("p").value
    const n_cars = document.getElementById("n_cars").value
    const cols   = document.getElementById("cols").value
    const rows   = document.getElementById("rows").value
    const mean   = document.getElementById("mean").value
    const sigma  = document.getElementById("sigma").value
    const min_l  = document.getElementById("min_l").value
    const max_l  = document.getElementById("max_l").value

    ipcRenderer.send("init", rows, cols, n_cars, p, mean, sigma, min_l, max_l);

    loading("block") //mostra gif caricamento
}

ipcRenderer.on("grafo", (event, grafo) => {

    loading("none") //nascondi gif caricamento
    switch_things() //mostra grafo e nascondi settings

    console.log("ecco il grafo da disegnare")
    console.log(grafo)

    grafo = JSON.parse(grafo)

    var counter = 0;
    for (i = 0; i < cols; i++){
        for (j = 0; j < rows; j++){

            s.graph.addNode({
                id: 'n'.concat(counter),
                x: i,
                y: j,
                size: 1,
                color: '#ff9000'

            })
            counter += 1
        }
    }

    counter = 0
    grafo["nodes"].forEach(node => {
        s.graph.addEdge({
            id: 'e'.concat(counter),
            source: 'n'.concat(node.x),
            target: 'n'.concat(node.y),
            type: "curvedArrow",
            color: '#fff',
            count: 1
        })
        counter += 1
    })

    s.refresh()

    })

var start = []
var end = []

function autocomplete_source_dest(){
    for (i=0; i < cols; i++){
        start.push(i)
        start.push(i*2)
    }
    for (i=(cols*rows) - cols*2; i < cols*rows; i++){
        end.push(i);
    }
}

function create_path(s, d){
    ipcRenderer.send("create_path", s, d)
}

function start_simulation(){
    ipcRenderer.send("start_simulation")
}


ipcRenderer.on("disegnami", (event, roba_da_disegnare) => {
    values = JSON.parse(roba_da_disegnare)
    values["streets"].forEach(element => {
        
        if (element.cars > 0){
            for (i=0; i < s.graph.edges().length; i++){
                //nota: stiamo confrontando interi e stringhe, ma js è figo e non ha problemi
                if (parseInt(s.graph.edges()[i].source.substr(1)) == element.street.x && parseInt(s.graph.edges()[i].target.substr(1)) == element.street.y){
                    if (element.cars/element.max <= 0.5)
                        s.graph.edges()[i].color = green;
                    else if (element.cars/element.max <= 0.75)
                        s.graph.edges()[i].color = orange;
                    else
                        s.graph.edges()[i].color = red;
                    break;
                }
            }
        } 

    });
    s.refresh();
})


