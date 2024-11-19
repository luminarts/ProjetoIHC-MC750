const socket = new WebSocket("ws://127.0.0.1:65432");
socket.onmessage = function(event) {
    // event.data é o que a gente recebe do arduino
};
