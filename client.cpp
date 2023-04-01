#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>

TcpClient::TcpClient(char* server_ip, int server_port)
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

    return true;
}

bool TcpClient::sendMessage(const char* message, size_t message_length) {
    ssize_t bytes_sent = send(client_fd, message, message_length, 0);
    if (bytes_sent == -1) {
        std::cerr << "Error sending message: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool TcpClient::receiveMessage(std::string& message) {
    constexpr size_t buffer_length = 1024;
    char buffer[buffer_length];

    ssize_t bytes_received = recv(client_fd, buffer, buffer_length, 0);
    if (bytes_received == -1) {
        std::cerr << "Error receiving message: " << strerror(errno) << std::endl;
        return false;
    }

    message.assign(buffer, bytes_received);
    std::cout << "Server response: " << message << std::endl;
    return true;
}
