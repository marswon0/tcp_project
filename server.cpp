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

#endif