#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <string>

class TcpClient {
public:
    TcpClient(char *server_ip, int server_port);
    ~TcpClient();

    bool connectToServer();
    bool sendMessage(const char *message, size_t length);
    bool receiveMessage(std::string& message);

private:
    int client_fd;
    int server_port;
    char *server_ip;
    sockaddr_in server_addr;
};

#endif
