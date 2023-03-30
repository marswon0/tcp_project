#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>

class TcpClient {
public:
    TcpClient(const char *server_ip, int server_port);
    ~TcpClient();

    bool connectToServer();
    bool sendMessage(const char *message, size_t length);
    bool receiveMessage(char *buffer, size_t length);

private:
    int client_fd;
    int server_port;
    sockaddr_in server_addr;
};

#endif
