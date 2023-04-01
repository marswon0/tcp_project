#include "server.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <future>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);
    TcpServer server(port);

    if (!server.start()) {
        std::cerr << "Failed to start the server." << std::endl;
        return 1;
    }

    std::cout << "Server started on port " << port << std::endl;

    std::vector<std::future<void>> client_threads;

    while (true) {
        int client_fd = server.acceptClient();
        if (client_fd == -1) {
            std::cerr << "Error accepting client connection." << std::endl;
            continue;
        }

        std::future<void> client_th = std::async(&TcpServer::handleClientThread, &server, client_fd);
        client_threads.push_back(std::move(client_th));
    }

    return 0;
}

