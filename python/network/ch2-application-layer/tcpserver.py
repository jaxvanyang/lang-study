from socket import *

server_port = 12000
server_socket = socket(AF_INET, SOCK_STREAM)

server_socket.bind(('', server_port))
server_socket.listen()

print('The server is ready to receive')

while True:
    connection_socket, addr = server_socket.accept()
    message = connection_socket.recv(1024).decode()
    modified_message = message.upper()
    connection_socket.send(modified_message.encode())
    connection_socket.close()
