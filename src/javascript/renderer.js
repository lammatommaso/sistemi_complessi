//const { BABYLON } = require('babylonjs')
//import { BABYLON } from 'babylonjs':

class Renderer {
    

    createScene(canvas, engine) {
        this._canvas = canvas;

        this._engine = engine;

        // This creates a basic Babylon Scene object (non-mesh)
        const scene = new BABYLON.Scene(engine);
        this._scene = scene;

        // This creates and positions a free camera (non-mesh)
        const camera = new BABYLON.FreeCamera("camera1", new BABYLON.Vector3(0, 5000, 0), scene);

        // This targets the camera to scene origin
        camera.setTarget(BABYLON.Vector3.Zero());

        // This attaches the camera to the canvas
        camera.attachControl(canvas, true);

        // This creates a light, aiming 0,1,0 - to the sky (non-mesh)
        const light = new BABYLON.HemisphericLight("light1", new BABYLON.Vector3(1, 1, 1), scene);

        // Default intensity is 1. Let's dim the light a small amount
        light.intensity = 0.5;

        // Our built-in 'sphere' shape. Params: name, subdivs, size, scene
        //const sphere = BABYLON.Mesh.CreateSphere("sphere1", 16, 2, scene);

        // Move the sphere upward 1/2 its height
        //sphere.position.y = 1;

        // Our built-in 'ground' shape. Params: name, width, depth, subdivs, scene
        const ground = BABYLON.Mesh.CreateGround("ground1", 4000, 4000, 2, scene);
        ground.position = BABYLON.Vector3.Zero();




        /*var sphere = BABYLON.Mesh.CreateSphere("sphere1", 16, 20, scene);
        var redMat = new BABYLON.StandardMaterial("redMat", scene);
	    redMat.emissiveColor = new BABYLON.Color3(1, 0, 0);

        sphere.position = new BABYLON.Vector3(3, 0, 3);
        sphere.material = redMat;*/

    }

    constructor(canvas) {
        const engine = new BABYLON.Engine(canvas, true);
        this.createScene(canvas, engine);

        engine.runRenderLoop(() => {
            this._scene.render();
        });

        window.addEventListener('resize', function () {
            engine.resize();
        });
    }
}

const renderer = new Renderer(document.getElementById('render-canvas'));