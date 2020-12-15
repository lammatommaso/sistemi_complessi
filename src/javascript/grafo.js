
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
    
        this.fattore_bordo = 15; //non vogliamo mettere i nodi esattamente nell'angolo estremo della superifice di base, ma vogliamo considerare un margine del fattore_bordo%

        this.nuovo_l1 = (lato1 - ((lato1/100)*this.fattore_bordo));
        this.nuovo_l2 = (lato2 - ((lato2/100)*this.fattore_bordo));
        this.distanza_tra_punti = this.nuovo_l1/(this.n - 1)
        this.larghezza = (this.nuovo_l1/this.n)/6; 

    }

    get matrice () {return this.matrix};
    get dimensione_lato() {return this.n};

    street2coordinates(i, j){
        var x1 = 0, x2 = 0;

        const fattore_bordo = this.fattore_bordo

        const lato = this.n;

        const nuovo_l1 = this.nuovo_l1

        const distanza_tra_punti = this.distanza_tra_punti

        const larghezza = this.larghezza


        if (i != j) {
       
            if (i == j-1) { //questo va perfettamente (0,1; 1,2; ... 7,8; etc.)
                x1 =  (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) - larghezza/4
                x2 = (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) + larghezza/4
            }
            
            
            if (i == j + 1){ // non va (1,0; 2,1; ... 8,7; etc.) 
                //FIXME funziona con 0,-1 ; 1,0; 2,1; ...
                //FIXME 8,5 lo disegna nella riga sopra
                 x1 = (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   )
                 x2 = (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) - larghezza/4
                
            }
            

            if (j == i+lato){ //questo funziona perfettamente
                if ((i+lato)%lato == lato-1){
                     x1 = (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) + distanza_tra_punti/2 - larghezza/4 
                     x2 = (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) - distanza_tra_punti/2 

                } else {
                    x1 = (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  )  - larghezza/4 
                    x2 = (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2) )
                }
            }

            if (i == j-lato ){ //questo non va
                if ((i+lato)%lato == lato-1){
                    x1 = (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) + distanza_tra_punti/2 + larghezza/4 
                    x2 = (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) - distanza_tra_punti/2
                } else {
                    x1 = (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  )  + larghezza/4 
                    x2 = (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2) )
                }
            }

        }

        return [x1, x2];
    
    }

    draw(){
        /* si potrebbe fare una funzione di esplorazione del grafo in ampiezza definendo eventualmente una prodondità massima: 
            1. piazziamo il nodo centrale del grafo al centro della scena
            2. disegnamo i nodi intorno al nodo centrale
            3. disegnamo i nodi intorno a questi e così via, fino a che non abbiamo disegnato tutto oppure ci fermiamo apposta prima (per 
                non far esplodere il pc - i nuovi nodi possono essere disegnati se l'utente sposta la vista)
        */ 
        const right_street_color = [new BABYLON.Color4(0, 1 ,0, 1), new BABYLON.Color4(0, 1 ,0, 1), new BABYLON.Color4(0 ,1, 0 , 1) , new BABYLON.Color4(0, 1 ,0, 1), new BABYLON.Color4(0, 255, 0, 1), new BABYLON.Color4(0, 255, 0, 1)]
        const left_street_color = [new BABYLON.Color3(1, 0.7, 0), new BABYLON.Color3(1, 0.7, 0), new BABYLON.Color3(1, 0.7, 0) , new BABYLON.Color3(1, 0.7, 0), new BABYLON.Color3(1, 0.7, 0), new BABYLON.Color3(1, 0.7, 0)]
        const asphalt_color = [new BABYLON.Color3(0.17, 0.18, 0.175), new BABYLON.Color3(0.17, 0.18, 0.175), new BABYLON.Color3(0.17, 0.18, 0.175) , new BABYLON.Color3(0.17, 0.18, 0.175), new BABYLON.Color3(0.17, 0.18, 0.175), new BABYLON.Color3(0.17, 0.18, 0.175)]
        const white = [new BABYLON.Color3(1, 1, 1), new BABYLON.Color3(1, 1, 1), new BABYLON.Color3(1, 1, 1) , new BABYLON.Color3(1, 1, 1), new BABYLON.Color3(1, 1, 1), new BABYLON.Color3(1, 1, 1)]
        
        const color4 = [new BABYLON.Color4(0 ,0.5, 0 , 1) , new BABYLON.Color4(0, 0.5 , 0, 1), new BABYLON.Color4(0, 0.9 ,0, 1), new BABYLON.Color4(0, 0.5, 0, 1)]
        
        const lato = this.n;

        const fattore_bordo = this.fattore_bordo

        const nuovo_l1 = this.nuovo_l1
        const nuovo_l2 = this.nuovo_l2

        const distanza_tra_punti = this.distanza_tra_punti

        const larghezza = this.larghezza
        
        for (let i = 0; i < lato; i++){
            for (let j = 0; j < lato; j++){
                var roundabout = BABYLON.MeshBuilder.CreateCylinder("cone", {height: 0.1, diameter: larghezza, faceColors: color4});

                roundabout.position = new BABYLON.Vector3((i*distanza_tra_punti - nuovo_l1/2) , 2.1, (j*distanza_tra_punti - nuovo_l2/2));
            }
        }
    
        for (let i = 0; i < lato*lato; i++){
            for (let j = 0; j < lato*lato; j++){

                if (i == 2 && j == 8){
                    console.log("test")
                }

                if (i != j) {
                    
                    /*strade orizzontali*/ 

                    if (j == i + 1 && j%lato != 0){
                        
                        var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: distanza_tra_punti, depth: (larghezza/2), faceColors: asphalt_color /*right_street_color*/});
                        //equazioni di dora l'esploratrice
                        box.position = new BABYLON.Vector3( (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) - larghezza/4, 2, (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) + larghezza/4); 
                        //traccio linea bianca al centro
                        var whiteline = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: distanza_tra_punti, depth: (larghezza/10), faceColors: white /*right_street_color*/});
                        //equazioni di dora l'esploratrice
                        whiteline.position = new BABYLON.Vector3( (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) , 2, (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) ); 
                    }
                    
                    if (i == j-1 && j%lato != 0) { //strade nell'altro senso, bisogna colorarle/disegnarci qualcosa per distinguerle?
                        var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: distanza_tra_punti, depth: (larghezza/2), faceColors: asphalt_color /*left_street_color*/});
                        //equazioni di dora l'esploratrice
                        box.position = new BABYLON.Vector3( (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ), 2, (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) - larghezza/4); 
                        
                    }
                    /*strade verticali*/ 

                    if (j == i+lato){ 
                        if ((i+lato)%lato == lato-1){
                            var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: (larghezza/2), depth: distanza_tra_punti, faceColors: asphalt_color /*right_street_color*/});
                            box.position = new BABYLON.Vector3( (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) + distanza_tra_punti/2 - larghezza/4 , 2, (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) - distanza_tra_punti/2 );                             

                            var whiteline = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: (larghezza/10), depth: distanza_tra_punti, faceColors: white });
                            whiteline.position = new BABYLON.Vector3( (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) + distanza_tra_punti/2  , 2, (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) - distanza_tra_punti/2 );                             

                        } else {
                            var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: (larghezza/2), depth: distanza_tra_punti, faceColors: asphalt_color /*right_street_color*/});
                            box.position = new BABYLON.Vector3( (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  )  - larghezza/4 , 2, (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2) ));     

                            var whiteline = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: (larghezza/10), depth: distanza_tra_punti, faceColors: white /*right_street_color*/});
                            whiteline.position = new BABYLON.Vector3( (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) , 2, (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2) ));     
                        }
                    }

                    if (j == i+lato ){ //strade nell'altro senso //TODO perché questa condizione è uguale a quella sopra?
                        if ((i+lato)%lato == lato-1){
                            var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: (larghezza/2), depth: distanza_tra_punti, faceColors: asphalt_color /*left_street_color*/});
                            box.position = new BABYLON.Vector3( (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2)   ) + distanza_tra_punti/2 + larghezza/4 , 2, (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  ) - distanza_tra_punti/2 );                             
                        } else {
                            var box = BABYLON.MeshBuilder.CreateBox("box", {height: 0.1, width: (larghezza/2), depth: distanza_tra_punti, faceColors: asphalt_color /*left_street_color*/});
                            box.position = new BABYLON.Vector3( (  (   ((parseInt(j/lato) + 1)*(nuovo_l1/(lato-1) )) - (nuovo_l1/(lato-1)*(parseInt(lato/2)+1)) ) + (nuovo_l1/(lato-1))/(2-(lato%2))*(1-lato%2)  )  + larghezza/4 , 2, (   (nuovo_l1/2 - ((nuovo_l1/(lato-1))*((i%lato) +1))) + nuovo_l1/((lato-1)*2) ));     
                        }
                    }

                }
            }
        }
    

    };


}
