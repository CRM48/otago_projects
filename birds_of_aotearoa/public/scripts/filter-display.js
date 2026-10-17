let filter_container = document.getElementById("filter-container");
let background_colour = document.getElementById("background-overlay");

function changeDisplay(status){
    filter_container.style.display = status;
    background_colour.style.display = status;
}

function filter_display(){
    changeDisplay("flex");
    status_outer.style.display = "none";
    size_outer.style.display = "none";
    //info_outer.style.display = "none";

    let exit = document.getElementById("close-window");
    exit.addEventListener("click", () => changeDisplay("none"));
}

/* Creates the two input checkboxes and radio buttons */
/* Easier to do in JavaScript rather than HTML as change is made easier if necessary */

let conservation_status = ["All", "Not Threatened", "Naturally Uncommon", "Relict", "Recovering", "Declining", "Nationally Increasing", "Nationally Vulnerable", "Nationally Endangered", "Nationally Critical", "Data Deficient"];
let size = ["All", "Small", "Medium", "Large"];
let info = ["All", "Image"]

let status_container = document.getElementById("status-container");
let size_container = document.getElementById("size-container");
let info_container = document.getElementById("info-container");
let status_outer = document.getElementById("status-outer");
let size_outer = document.getElementById("size-outer");
let info_outer = document.getElementById("info-outer");

for(const statusObject of conservation_status){
    let status_label = document.createElement("label");
    let status_input = document.createElement("input");
    status_label.setAttribute("class", "status-label");
    status_label.setAttribute("for", statusObject === "All" ? `${statusObject}-status` : statusObject);
    status_input.setAttribute("name", statusObject === "All" ? `${statusObject}-status` : statusObject);
    status_input.setAttribute("class", "status-input");
    status_label.setAttribute("id", `${statusObject}-status-label`);
    status_input.setAttribute("id", `${statusObject}-status-checkbox`);
    status_input.setAttribute("type", "checkbox");
    
    status_label.append(status_input);
    status_label.append(document.createTextNode(statusObject));
    status_container.append(status_label);
}

for(const sizeObject of size){
    let size_label = document.createElement("label");
    let size_input = document.createElement("input");
    size_label.setAttribute("class", "size-label");
    size_input.setAttribute("name", "size");
    size_input.setAttribute("class", "size-input");
    size_label.setAttribute("id", `${sizeObject}-size-label`);
    size_input.setAttribute("id", `${sizeObject}-size-checkbox`);
    size_input.setAttribute("type", "radio");
    size_input.setAttribute("value", sizeObject);
    
    size_label.append(size_input);
    size_label.append(document.createTextNode(sizeObject));
    size_container.append(size_label);
}

/* sets the size and status buttons to display/not display their list of choices */
/* I coded out an option to have the selection of one cause the other to close 
as I decided I prefered the aesthetic of both being individually changed, I kept
the code in case I change my mind */
let status_button = document.getElementById("status-button");
status_button.addEventListener("click", () => {
    status_outer.style.display = status_outer.style.display === "flex" ? "none" : "flex";
    /*
    size_outer.style.display = "none";
    info_outer.style.display = "none";
    }
    */
});

let size_button = document.getElementById("size-button");
size_button.addEventListener("click", () => {
    size_outer.style.display = size_outer.style.display === "flex" ? "none" : "flex";
    /*
    status_outer.style.display = "none";
    info_outer.style.display = "none";
    */
});

/* Creation of sort bar */

let sort_options = ["M\u0101ori name", "English Name", "Scientific Name", "Photographer", "Family", "Order", "Conservation Status", "Lightest to Heaviest", "Heaviest to Lightest", "Shortest to Longest", "Longest to Shortest"];
let sort = document.getElementById("sort");

for(const sortObject of sort_options){
    let sort_option = document.createElement("option");
    sort_option.setAttribute("value", sortObject);
    sort_option.textContent = sortObject;
    sort.append(sort_option);
}

/* required variables */
let all_status = document.getElementById("All-status-checkbox");
let all_size = document.getElementById("All-size-checkbox");
let all_info = document.getElementById("All-info-checkbox");
let statInput = document.querySelectorAll(".status-input");
let checkedStatValues = [];
let sizeInput = document.querySelectorAll(".size-input");
let sizeChoice;

/* sets the checkboxes to be auto selected at start */
/* I removed an option to have them always be set to on when you open
the filter tab (see filter_status) as I figured it was better to let
the user see their old filter and make changes accordingly */
all_status.checked = true;
all_size.checked = true;

/* code to make the all option in status turn off all other options
and all other options turn off the all button */
let rest = document.querySelectorAll(".status-input");

/**
 * Allows proper functionality for All button
 * @param {Object} event 
 */
function allSelect(event){
    let checkedBox = event.target;
    if(checkedBox === all_status){
        if(checkedBox.checked){
            rest.forEach(checkbox => checkbox.checked = false);
            all_status.checked = true;
        }
    }
    else{
        if(checkedBox.checked){
            all_status.checked = false;
        }
    }
}

all_status.addEventListener("change", allSelect);
rest.forEach((checkbox) => {
  checkbox.addEventListener("change", allSelect);
});

/* Button that opens the filter display */
let open_filter = document.querySelector("#filter-button");
open_filter.addEventListener('click', filter_display);