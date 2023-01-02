from socket import *

server_name = 'localhost'
server_port = 12000

client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((server_name, server_port))

message = input('Input lowercase message: ')
client_socket.send(message.encode())

modified_message = client_socket.recv(1024)
print('From server:', modified_message.decode())

client_socket.close()
