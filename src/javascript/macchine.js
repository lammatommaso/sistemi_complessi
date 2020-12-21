
class Macchine {
    


    constructor(numero_macchine){ 
        this.numero_macchine = numero_macchine;
        this.macchine = new Array(numero_macchine);
    }

    get n_macchine () {return this.numero_macchine};

    draw(id_macchina, x, y, z, rot1, rot2, rot3){

        const red = [new BABYLON.Color3(1, 0.7, 0), new BABYLON.Color3(1, 0.7, 0), new BABYLON.Color3(1, 0.7, 0) , new BABYLON.Color3(1, 0.7, 0), new BABYLON.Color3(1, 0.7, 0)]

        if (!this.macchine[id_macchina]){
            const shape = BABYLON.Mesh.CreatePolyhedron("shape" + 5, {type: 5,  size: lato1/120, sizeY: lato1/55, faceColors: red}, window._scene);
            this.macchine.push(shape)
            shape.position = new BABYLON.Vector3(x, y, z); 
            shape.rotation = new BABYLON.Vector3(rot1, rot2, rot3);
            //shape.rotation = new BABYLON.Vector3(0.7,-0.9,-0.8) 
        } else {
            const shape = this.macchine[id_macchina]
            shape.position = new BABYLON.Vector3(x, y, z); 
            shape.rotation = new BABYLON.Vector3(rot1, rot2, rot3);
            //shape.rotation = new BABYLON.Vector3(0.7,-0.9,-0.8) 
        
        }

        //shape.rotation = new BABYLON.Vector3(0.7,-0.9,-0.8) 
    }    
}
