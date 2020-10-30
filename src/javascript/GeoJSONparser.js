//TODO googla oboe.js per parsare json caricato come stream
//TODO parsa il file GeoJSON per controllare che sia valido, prima di fare la seconda passata per disegnare i valori

ipcRenderer.send("load_map")

ipcRenderer.on("load_map", (event, mappa) => {

    //mappa = JSON.parse(map)

    try {
      if (mappa["type"] == "FeatureCollection"){
        mappa["features"].forEach((feature, index) => {
          parse_feature(feature);
        });
      } else if (mappa["type"] == "Feature"){
        parse_feature(mappa)
      } else {
        throw `Not a valid GeoJSON file! type ${mappa["type"]} not defined`
      }
      //un oggetto GeoJson può avere anche altri membri
      //Un oggetto GeoJson può avere anche un membro bbox - vedi parse_feature

    } catch(exc){
      console.error(exc)
    }

    /********* FUNZIONI *********************************************************************/

    function parse_feature(feature){
      switch(feature["geometry"]["type"]){
        case "Point":
          break;
        case "MultiPoint":
          break;
        case "LineString":
          break;
        case "MultiLineString":
          break;
        case "Polygon":
          break;
        case "MultiPolygon":
          break;
        case "GeometryCollection":
          break;
        default:
          throw `Not a valid GeoJSON file! geometry ${feature["geometry"]} not defined`
      }

      parse_position(feature["geometry"]["coordinates"], feature["geometry"]["type"])
      //ogni Feature ha un campo properties


      //ogni Feature può avere un campo id
      if(feature.hasOwnProperty('id')){
        //do something
      }

      //Una feature può avere un campo bbox
      if(feature.hasOwnProperty('bbox')){
        //do something
      }

    }

    function parse_type( element ){

    }
    function parse_geometry( element ){

    }

    function parse_point(){

    }

    function parse_multipoint(){

    }

    function parse_linestring(){

    }

    function parse_polygon(){

    }

    function parse_multipolygon(){

    }

    function parse_geometry_collection(){

    }

    function parse_position(position, type){
      switch(type){
        case "Point":
          
          var scene = this._scene
          var sphere = BABYLON.Mesh.CreateSphere("sphere1", 16, 20, scene);
          var redMat = new BABYLON.StandardMaterial("redMat", scene);
          redMat.emissiveColor = new BABYLON.Color3(1, 0, 0);

          var myPosition = convert_coordinates(parseFloat(position[0]), parseFloat(position[1]))
          console.log("Disegno punto " + myPosition.x + ", " + myPosition.y)
          sphere.position = new BABYLON.Vector3(myPosition.x, 0, myPosition.y);
          sphere.material = redMat;
          //la posizione deve essere singola
          //devono esserci 2 numeri (lat/lon oppure x/y) e opzionalmente un terzo numero come altitudine
          //converti lat/lon in x/y e disegnali sulla mappa
          break;
        case "LIneString":
        case "MultiPoint":
          //array di posizioni
          position.forEach((pos, i) => {
            //vedi Point
          });

          break;
        case "Polygon":
        case "MultiLineString":
          //array di LineString
          position.forEach((LineString, i) => {
            LineString.forEach((pos, j) => {
              //vedi Point
              //Polygon: la prima e l'ultima posizione devono coincidere
            });

          });

          break;
        case "MultiPolygon":
          //array di coordinate Polygon
          position.forEach((Polygon, i) => {
            Polygon.forEach((pos, i) => {

            });

          });

          break;
        case "GeometryCollection":
          position["geometries"].forEach((geometry, i) => {
            parse_position(geometry)
          });

          break;
        default:
          throw `Not a valid GeoJSON file! Invalid coordinates ${position} for the type ${type}`
      }
    }

    function convert_coordinates(lat, lon){
      var MAP_WIDTH = 1000000;
      var MAP_HEIGHT = 1000000;

      var y = (((-1 * lat) + 90) * (MAP_HEIGHT / 180)) - 256100;
      var x = ((lon + 180) * (MAP_WIDTH / 360)) - 656000;
      return {x:x,y:y};
    }




})
