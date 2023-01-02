# TODO: merge tcpserver by multi-process

from socket import *

bufsize = 2048

server_port = 12000
server_socket = socket(AF_INET, SOCK_DGRAM)
server_socket.bind(('', server_port))
print('The server is ready to receive')

while True:
    message, client_address = server_socket.recvfrom(bufsize)
    modified_message = message.decode().upper()
    server_socket.sendto(modified_message.encode(), client_address)
