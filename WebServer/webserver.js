const express = require('express');
const bodyParser = require('body-parser');
const WebSocket = require('ws');

const app = express();
const wss = new WebSocket.Server({ noServer: true });

let dataFromESP32;

// Middleware per analizzare il corpo delle richieste POST
app.use(bodyParser.json());

// Rotta per ricevere i dati dall'ESP32
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

// Rotta per visualizzare i dati
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




const server = app.listen(3000, () => console.log(`Server in esecuzione su http://192.168.1.101:3000`));

wss.on('connection', ws => {
    ws.on('message', message => {
        console.log(`Received message => ${message}`)
    });
    if (dataFromESP32) {
        ws.send(JSON.stringify(dataFromESP32));
    }
});

server.on('upgrade', (request, socket, head) => {
    wss.handleUpgrade(request, socket, head, ws => {
        wss.emit('connection', ws, request);
    });
});
