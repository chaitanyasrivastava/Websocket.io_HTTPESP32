const WebSocket = require('ws');

const PORT = 8000;
const server = new WebSocket.Server({ host: '0.0.0.0', port: PORT });  // Bind to all network interfaces

server.on('connection', (ws) => {
    console.log("ESP8266 Connected");

    ws.on('message', (message) => {
        console.log("Received from ESP8266:", message);
        ws.send("Echo: " + message);  // Send response back to ESP8266
    });

    ws.on('close', () => {
        console.log("ESP8266 Disconnected");
    });
});

console.log(`WebSocket server running on ws://0.0.0.0:${PORT}`);
