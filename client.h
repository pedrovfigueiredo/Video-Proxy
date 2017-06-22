#ifndef CLIENT_H
#define CLIENT_H
#include "Thread.h"
#include <string>


class Client : public Thread
{
public:

    enum priority {
        High, Low
    };


    Client(Buffer& buffer, std::string IP, std::string port);
    virtual ~Client();
    void buildSocket();
    void streamVideo();
    void run();
    void stop();
    void resume();
    void readBuffer();

    Semaphore* sem_stopped;
    bool stopped = false;
    priority priorityLevel = priority::Low;

private:

    char localFrame[DATA_SIZE];
    int localFront = 0;


    int sock, length;
    struct sockaddr_in server;
    struct hostent *hp;

};

#endif // CLIENT_H
