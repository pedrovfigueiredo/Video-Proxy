#include "buffer.h"

Buffer::Buffer()
{
    empty = new Semaphore(BUFFER_SIZE);
    full = new Semaphore(0);
    mutexF = new Semaphore(1);
    lowP = new Semaphore(0);
    highP = new Semaphore(0);
}

Buffer::~Buffer(){
    delete empty;
    delete full;
    delete mutexF;
    delete lowP;
    delete highP;
}
