#include "server.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

constexpr int BUFFER_SIZE = 1024;

TcpServer::TcpServer(int port) : server_fd(-1), port(port), running(false) {
}

TcpServer::~TcpServer() {
    stop();
}

bool TcpServer::start() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        return false;
    }

    if (listen(server_fd, 5) == -1) {
        std::cerr << "Error listening on socket" << std::endl;
        return false;
    }

    running = true;
    return true;
}

void TcpServer::stop() {
    if (server_fd != -1) {
        close(server_fd);
        server_fd = -1;
    }
    running = false;
}


int TcpServer::acceptClient() {
    if (server_fd == -1) {
        std::cerr << "Server not started." << std::endl;
        return -1;
    }

    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);
    if (client_fd == -1) {
        std::cerr << "Error accepting client connection: " << strerror(errno) << std::endl;
        return -1;
    }

    return client_fd;
}


void TcpServer::closeClient(int client_fd) {
    if (client_fd == -1) {
        std::cerr << "Invalid client file descriptor." << std::endl;
        return;
    }

    if (close(client_fd) == -1) {
        std::cerr << "Error closing client connection: " << strerror(errno) << std::endl;
    }
}


void TcpServer::handleClient(int client_fd) {
    constexpr size_t buffer_length = 1024;
    char buffer[buffer_length];

    while (running) {
        ssize_t bytes_received = recv(client_fd, buffer, buffer_length, 0);
        if (bytes_received <= 0) {
            if (bytes_received == -1) {
                std::cerr << "Error receiving message from client: " << strerror(errno) << std::endl;
            }
            break;
        }

        std::cout << "Received message from client: " << std::string(buffer, bytes_received) << std::endl;

        // Echo the message back to the client
        ssize_t bytes_sent = send(client_fd, buffer, bytes_received, 0);
        if (bytes_sent == -1) {
            std::cerr << "Error sending message to client: " << strerror(errno) << std::endl;
            break;
        }
    }

    close(client_fd);
}

void TcpServer::handleClientThread(int client_fd) {
    this->handleClient(client_fd);
    this->closeClient(client_fd);
}