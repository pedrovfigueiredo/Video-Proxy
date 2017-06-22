#include "semaphore.h"

Semaphore::Semaphore(int count):
count_(count)
{}

void Semaphore::V(){
    std::unique_lock<std::mutex> lck(mtx);
    ++count_;
    cv.notify_one();
}

void Semaphore::P(){
    std::unique_lock<std::mutex> lck(mtx);

    while(count_ == 0)
      cv.wait(lck);

    --count_;
}


