const express = require('express');
const path = require('path');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.listen(PORT, () => {
    console.log(`Server is running at http://localhost:${PORT}`);
});
const port = new SerialPort('COM3', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));

parser.on('data', (data) => {
    console.log(`Received data from Arduino: ${data}`);
});

port.write('Hello from Node.js\n');