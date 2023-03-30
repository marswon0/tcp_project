#include "client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

TcpClient::TcpClient(const char *server_ip, int server_port) : client_fd(-1), server_port(server_port) {
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_aton(server_ip, &server_addr.sin_addr);
}

TcpClient::~TcpClient() {}
