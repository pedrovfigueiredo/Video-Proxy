#ifndef BUFFER_H
#define BUFFER_H
#define DATA_SIZE 1316
#define BUFFER_SIZE 1000
#include "semaphore.h"

typedef struct{
    char frame [DATA_SIZE];
}tData;

class Buffer
{
public:
    Buffer();
    virtual ~Buffer();
    tData data[BUFFER_SIZE];

    // Producer Consumer
    Semaphore* empty;
    Semaphore* full;
    Semaphore* mutexF;

    // Number of consumers
    int consumersCount = 0;

    //Reader Writer
    int dlowP = 0;
    int dhighP = 0;
    int nlowP = 0;
    int nhighP = 0;
    Semaphore* lowP;
    Semaphore* highP;

    int numActiveThreads = 0;


};

#endif // BUFFER_H
