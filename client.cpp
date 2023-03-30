#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

TcpClient::TcpClient(const char* server_ip, int server_port)
    : client_fd(-1), server_ip(server_ip), server_port(server_port) {
}

TcpClient::~TcpClient() {
    if (client_fd != -1) {
        close(client_fd);
    }
}

bool TcpClient::connectToServer() {
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
        return false;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_aton(server_ip, &server_addr.sin_addr) == 0) {
        std::cerr << "Error converting IP address: " << strerror(errno) << std::endl;
        return false;
    }

    if (connect(client_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "Error connecting to server: " << strerror(errno) << std::endl;
        return false;
    }

    return