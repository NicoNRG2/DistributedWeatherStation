//framework express 
const express = require('express');
const bodyParser = require('body-parser');
const WebSocket = require('ws');

const app = express();
const wss = new WebSocket.Server({ noServer: true });
//store data from esp32
let dataFromESP32;

// Middleware to analize the json 
app.use(bodyParser.json());

// Route to receive data from the ESP32 via a POST request
app.post('/data', (req, res) => {
    console.log(req.body);
    dataFromESP32 = req.body;
    res.send('Dati ricevuti con successo!');
    wss.clients.forEach(client => {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(dataFromESP32));
        }
    });
});

// Routes for serving static files
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});
app.get('/enego_station.html', (req, res) => {
    res.sendFile(__dirname + '/enego_station.html');
});
app.get('/marostica_station.html', (req, res) => {
    res.sendFile(__dirname + '/marostica_station.html');
});
app.get('/index.html', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});



// Starting the Express server on a given port and IP address
const server = app.listen(3000, () => console.log(`Server in esecuzione su http://192.168.1.101:3000`));
// Management of WebSocket connections
wss.on('connection', ws => {
    //message received
    ws.on('message', message => {
        console.log(`Received message => ${message}`)
    });
    
    // Send stored data from the ESP32 to the newly connected WebSocket client
    if (dataFromESP32) {
        ws.send(JSON.stringify(dataFromESP32));
    }
});
//WebSocket protocol update management
server.on('upgrade', (request, socket, head) => {
    wss.handleUpgrade(request, socket, head, ws => {
        wss.emit('connection', ws, request);
    });
});
