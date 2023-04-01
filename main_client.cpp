#include "client.h"
#include <iostream>
#include <chrono>
#include <thread>

constexpr int BUFFER_SIZE = 1024;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server IP> <server port>" << std::endl;
        return 1;
    }

    char *server_ip = argv[1];
    int server_port = atoi(argv[2]);

    TcpClient client(server_ip, server_port);

    if (!client.connectToServer()) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    int message_count = 0;
    char buffer[BUFFER_SIZE];

    while (true) {
        std::string message = "Message count: " + std::to_string(message_count);
        client.sendMessage(message.c_str(), message.length());
        std::cout << "Sent: " << message << std::endl;
	
        std::string server_respond;
        if (client.receiveMessage(server_respond)) {
            std::cout << "Received: " << server_respond << std::endl;
        } else {
            std::cerr << "Error receiving message" << std::endl;
            break;
        }

        message_count++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
