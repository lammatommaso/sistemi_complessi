function switch_things(){
    if (!(document.getElementById("settings").style.display == "none")){ //settings è visibile
        document.getElementById("graph").style.display = "block"; 
        document.getElementById("settings").style.display = "none";
    } else { //settings non è visibile
        document.getElementById("graph").style.display = "none"; 
        document.getElementById("settings").style.display = "block";
    }
}

function loading(status){
    document.getElementById("loading").style.display = status

}