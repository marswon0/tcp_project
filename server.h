#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

class TcpServer {
public:
    TcpServer(int port);
    ~TcpServer();

    bool start();
    void stop();

private:
    int server_fd;
    int port;
    sockaddr_in server_addr;
    bool running;
};

#endif
