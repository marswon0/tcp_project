#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <thread>

class TcpServer {
public:
    TcpServer(int port);
    ~TcpServer();

    bool start();
    void stop();
    int acceptClient();
    void closeClient(int client_fd);
    void handleClient(int client_fd);
    void handleClientThread(int client_fd);

private:
    int server_fd;
    int port;
    sockaddr_in server_addr;
    bool running;
};

#endif
