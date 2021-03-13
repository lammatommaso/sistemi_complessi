const green  = "#9bee00"
const orange = "#ffaa00"
const red    = "#f00"

const source_node_color = "#4dabf7"
const dest_node_color = "#be4bdb"
const normal_node_color = "#ff9000"

var s = new sigma({
renderer:{
    container: 'main', 
    type: 'canvas'
},
settings: {
    minArrowSize: 10,
    minEdgeSize: 2,
    maxEdgeSize: 5
}
})

s.bind('clickNode', function(e) {
    var nodeId = e.data.node.id
    node_color = e.data.node.color;
    switch(node_color){
        case normal_node_color:
            e.data.node.color = source_node_color
            break;
        case source_node_color:
            e.data.node.color = dest_node_color;
            break;
        case dest_node_color:
            e.data.node.color = normal_node_color;
            break;
        default:
            break;
    }
    s.refresh();

    //console.log(e)
})


var p      = 0;
var n_cars = 0;
var cols   = 0;
var rows   = 0;
var mean   = 0;
var _sigma = 0;
var min_l  = 0;
var max_l  = 0;

function init(){
    p      = parseFloat(document.getElementById("p").value)
    n_cars = parseInt(document.getElementById("n_cars").value)
    cols   = parseInt(document.getElementById("cols").value)
    rows   = parseInt(document.getElementById("rows").value)
    mean   = parseInt(document.getElementById("mean").value)
    _sigma = parseInt(document.getElementById("sigma").value)
    min_l  = parseInt(document.getElementById("min_l").value)
    max_l  = parseInt(document.getElementById("max_l").value)

    ipcRenderer.send("init", p,  n_cars, rows, cols,  mean, _sigma, min_l, max_l);

    loading("block") //mostra gif caricamento
}

ipcRenderer.on("grafo", (event, grafo) => {
    
    s.graph.clear();
    loading("none") //nascondi gif caricamento
    switch_things() //mostra grafo e nascondi settings

    grafo = JSON.parse(grafo)

    var counter = 0;
    for (i = 0; i < cols; i++){
        for (j = 0; j < rows; j++){

            s.graph.addNode({
                id: 'n'.concat(counter),
                x: i,
                y: j,
                size: 1,
                color: normal_node_color

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
            size: 1,
            count: 1
        })
        counter += 1
    })

    s.refresh()
    s.refresh()

    autocomplete_source_dest();
    create_path(start, end);

})

var start = []
var end = []

function autocomplete_source_dest(){ //funzione molto basica
    //Usiamo il 65% dei nodi come nodi di partenza o di arrivo
    //ovvero il 32.5 come partenza, il 32.5 come arrivo
    var tot_nodi = cols*rows;
    var perc_nodi = parseInt((tot_nodi/100)*65)
    for (i=0; i < parseInt(perc_nodi/2); i++){
        start.push(i)
    }
    for (i=(cols*rows) - parseInt(perc_nodi/2); i < cols*rows; i++){
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
    values = roba_da_disegnare //JSON.parse(roba_da_disegnare)
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


