const express = require('express');
const path = require('path');
const { SerialPort } = require('serialport'); // Correct import
const { ReadlineParser } = require('@serialport/parser-readline'); // Correct import
const http = require('http'); // For Socket.IO
const { Server } = require('socket.io'); // For Socket.IO

const app = express();
const PORT = 3000;

const server = http.createServer(app);
const io = new Server(server);

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Start the server
server.listen(PORT, () => {
  console.log(`Server is running at http://localhost:${PORT}`);
});

// Set up SerialPort
const port = new SerialPort({ path: 'COM3', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' })); // Correct instantiation

// Listen for data from the Arduino
parser.on('data', (data) => {
  console.log(`Received data from Arduino: ${data}`);
  // Emit the data to all connected clients
  io.emit('arduinoData', data.trim());
});

// Optional: Write to Arduino
port.write('Hello from Node.js\n');

// Handle client connections
io.on('connection', (socket) => {
  console.log('A user connected');

  socket.on('disconnect', () => {
    console.log('A user disconnected');
  });
});
