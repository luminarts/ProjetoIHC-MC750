import socket
import pygame

HOST = '127.0.0.1'
PORT = 65432

audio_files = {"1": "Sol.mp3",
               "2": "Lua.mp3",
               "3": "Terra.mp3"}

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    client_socket.connect((HOST, PORT))
    while True:
        data = client_socket.recv(1024).decode('utf-8')
        if data:
            # Lógica do som aqui:
            if data in audio_files:
                pygame.mixer.init()
                pygame.mixer.music.load(audio_files[data])
                pygame.mixer.music.play()
                while pygame.mixer.music.get_busy():
                    continue


