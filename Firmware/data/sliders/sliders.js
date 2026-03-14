var sliderX = document.getElementById("Xslider");
var outputX = document.getElementById("Xvalue");
outputX.innerHTML = sliderX.value;

sliderX.oninput = function () {
    outputX.innerHTML = this.value;
    if (stop && this.value % 5 == 0) {
        sendXPos(this.value);
    }
}

var sliderY = document.getElementById("Yslider");
var outputY = document.getElementById("Yvalue");
outputY.innerHTML = sliderY.value;

sliderY.oninput = function () {
    outputY.innerHTML = this.value;
    if (stop && this.value % 5 == 0) {
        sendYPos(this.value);
    }
}

var sliderZ = document.getElementById("Zslider");
var outputZ = document.getElementById("Zvalue");
outputZ.innerHTML = sliderZ.value;

sliderZ.oninput = function () {
    outputZ.innerHTML = this.value;
    if (stop && this.value % 5 == 0) {
        sendZPos(this.value);
    }
}



function sendXPos(val) {
    websocket.send(JSON.stringify({ 'action': 'posX', 'pos': val }));
}
function sendYPos(val) {
    websocket.send(JSON.stringify({ 'action': 'posY', 'pos': val }));
}
function sendZPos(val) {
    websocket.send(JSON.stringify({ 'action': 'posZ', 'pos': val }));
}