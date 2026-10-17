let container = document.querySelector("#birds_container");
function key(){
    let key_panel = document.getElementById("key_panel");
    if(key_panel.style.display == "block"){
        container.style.padding = "0";
        container.style.right = "0";
        key_panel.style.display = "none";
        return;
    }
    container.style.padding = "0 0 0 300px";
    container.style.right = "0";
    key_panel.style.display = "block";

}

/* Button that opens the key */
let key_button = document.querySelector("#key-button");
key_button.addEventListener('click', key);