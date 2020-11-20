
class Grafo {
    //rappresentato con matrice di adiacenza
    constructor(n){ //n è la dimensione del lato (es. n = 3 => grafo di 3x3 => matrice di adiacenza di 9x9)
        this.n = n;
        this.matrix =[];
        for (let i = 0; i < n*n; i++){
            this.matrix[i] = [];
            for (let j = 0; j < n*n; j++){
                if ( (i != j) && ( (j == i + 1 && j%n != 0) || (j == i-1 && i%n != 0) || (j == i+n) || (j == i-n) ) ){
                    this.matrix[i][j] = 1;
                } else 
                    this.matrix[i][j] = 0;
            }       
        }
    
    }

    get matrice () {return this.matrix};
    get dimensione_lato() {return this.n};

    draw(){
        /* si potrebbe fare una funzione di esplorazione del grafo in ampiezza definendo eventualmente una prodondità massima: 
            1. piazziamo il nodo centrale del grafo al centro della scena
            2. disegnamo i nodi intorno al nodo centrale
            3. disegnamo i nodi intorno a questi e così via, fino a che non abbiamo disegnato tutto oppure ci fermiamo apposta prima (per 
                non far esplodere il pc - i nuovi nodi possono essere disegnati se l'utente sposta la vista)
        */ 
        const color6 = [new BABYLON.Color4(0, 1 ,0, 1), new BABYLON.Color4(0, 1 ,0, 1), new BABYLON.Color4(0 ,1, 0 , 1) , new BABYLON.Color4(0, 1 ,0, 1), new BABYLON.Color4(0, 255 ,0, 1), new BABYLON.Color4(0, 255, 0, 1)]
        const color4 = [new BABYLON.Color4(0 ,0.5, 0 , 1) , new BABYLON.Color4(0, 0.5 , 0, 1), new BABYLON.Color4(0, 0.9 ,0, 1), new BABYLON.Color4(0, 0.5, 0, 1)]
        
        const lato = this.n;
        const fattore_bordo = 15; //non vogliamo mettere i nodi esattamente nell'angolo estremo della superifice di base, ma vogliamo considerare un margine del fattore_bordo%

        const nuovo_l1 = (lato1 - ((lato1/100)*fattore_bordo));
        const nuovo_l2 = (lato2 - ((lato2/100)*fattore_bordo));

        const distanza_tra_punti = nuovo_l1/(this.n - 1)

        for (let i = 0; i < lato; i++){
            for (let j = 0; j < lato; j++){
                var roundabout = BABYLON.MeshBuilder.CreateCylinder("cone", {height: 0.1, diameter: 1.5, faceColors: color4});
                roundabout.position = new BABYLON.Vector3((i*distanza_tra_punti - nuovo_l1/2) , 3, (j*distanza_tra_punti - nuovo_l2/2));
            }
        }
        
        /*for (let i = 0; i < lato*lato; i++){
            for (let j = 0; j < lato*lato; j++){
                
                if (i != j) {
                    
                    if ( (j == i + 1 && j%lato != 0) || (j == i-1 && i%lato != 0)) {
                        var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: distanza_tra_punti, depth: 1.5, faceColors: color6});
                        box.position = new BABYLON.Vector3((i%lato)*(distanza_tra_punti/2) - nuovo_l1/2, 2,(j%lato)*(distanza_tra_punti/2) - nuovo_l2/2)
                    //console.log("Disegno nodo in posizione " + (i*distanza_tra_punti - nuovo_l1/2) + ", " + (j*distanza_tra_punti - nuovo_l2/2))
                    }

                    if ((j == i+lato) || (j == i-lato)){
                        var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: 1.5, depth: distanza_tra_punti, faceColors: color6});
                        box.position = new BABYLON.Vector3((i%lato)*(distanza_tra_punti) - nuovo_l1/2 , 2, (j%lato)*(distanza_tra_punti) - nuovo_l2/2)                    
                    }
                }
            }
        }*/

    };
}
