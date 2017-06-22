#ifndef SERVER_H
#define SERVER_H
#include "Thread.h"

class Server : public Thread
{
public:
    Server(Buffer& buffer, std::string IP, std::string port);
    ~Server();

    void buildSocket();

    void populateBuffer();

    void run();

    void receivePackages();

private:

    char localFrame [DATA_SIZE];

    int rear = 0;

    int sock, length;
    socklen_t fromlen;
    struct sockaddr_in server;
    struct sockaddr_in from;
};

#endif // SERVER_H
