import serial
import socket
import threading

# Serial port configuration
SERIAL_PORT = 'COM3'  # Replace with your Arduino's serial port
BAUD_RATE = 9600

# Socket server configuration
HOST = '127.0.0.1'
PORT = 65432

# Function to handle client connections
def handle_client(client_socket):
    while True:
        try:
            data = serial_connection.readline().decode('utf-8').strip()
            client_socket.sendall(data.encode('utf-8'))
        except:
            break

# Open the serial port
serial_connection = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Set up the socket server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(5)

print(f"Server started on {HOST}:{PORT}")
try:
    while True:
        client_sock, addr = server_socket.accept()
        print(f"Client connected: {addr}")
        client_handler = threading.Thread(target=handle_client, args=(client_sock,))
        client_handler.start()
except KeyboardInterrupt:
    print("Shutting down server...")
finally:
    server_socket.close()
    serial_connection.close()
