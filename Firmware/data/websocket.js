var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

var x = 0;
var y = 0;
var z = 0;

var velocity = 0;

var stop = false;


window.addEventListener('load', onLoad);


function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage; // <-- add this line
}
function onOpen(event) {
    console.log('Connection opened');
}
function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}



function onMessage(event) {
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj);

    for (var i = 0; i < keys.length; i++) {
        var key = keys[i];
        document.getElementById(key).innerHTML = myObj[key];
    }
}

/*function onMessage(event) {
    let data = JSON.parse(event.data, function (key, value) {
        if (key == "posx") {
            var tmp = 0;
            for (i = 0; i < value.length(); i++) {
                tmp += value.charAt(i);
            }
            x = parseInt(tmp);
            changePos();
        }

        if (key == "vel") {
            velocity = parseInt(value);
        }
    });
}*/



function initButton() {
    document.getElementById('hexagon').addEventListener('click', hexagon_proccess);
    document.getElementById('triangle').addEventListener('click', triangle_proccess);
    document.getElementById('rectangle').addEventListener('click', rectangle_proccess);
    document.getElementById('rhombus').addEventListener('click', rhombus_proccess);
    document.getElementById('stop').addEventListener('click', stop_proccess);
}



function changeStateBox(text) {
    document.getElementById('state_box').innerHTML = "<br><br>" + "STATE: " + "<strong>" + text + "</strong>";
}

function changePos() {
    document.getElementById('positions').innerHTML = "X: " + x + "<br>" + "Y: " + y + "<br>" + "Z: " + z;
}

function changeVelocity() {
    document.getElementById('velocity').innerHTML = "effector velocity:<br>" + velocity + " m/s";
}



function stop_proccess() {
    stop = !stop;
    if (!stop)
        changeStateBox('figures');
    else
        changeStateBox('sliders');
    websocket.send(JSON.stringify({ 'action': 'stop' }));
}
function hexagon_proccess() {
    if (!stop) {
        changeStateBox('hexagon');
        websocket.send(JSON.stringify({ 'action': 'hexagon' }));
    }
}
function triangle_proccess() {
    if (!stop) {
        changeStateBox('triangle');
        websocket.send(JSON.stringify({ 'action': 'triangle' }));
    }
}
function rectangle_proccess() {
    if (!stop) {
        changeStateBox('rectangle');
        websocket.send(JSON.stringify({ 'action': 'rectangle' }));
    }
}
function rhombus_proccess() {
    if (!stop) {
        changeStateBox('rhombus');
        websocket.send(JSON.stringify({ 'action': 'rhombus' }));
    }
}





function transporter_proccess() {
    websocket.send(JSON.stringify({ 'action': 'transporter' }));
}

function robot_proccess() {
    websocket.send(JSON.stringify({ 'action': 'robot' }));
}








function onLoad(event) {
    initWebSocket();
    initButton();

    changeStateBox("figures");
}
