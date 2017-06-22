/*
 * Thread.h
 *
 *  Created on: 16 de abr de 2017
 *      Author: Suporte
 */

#ifndef THREAD_H_
#define THREAD_H_
#include <pthread.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include "buffer.h"
#include "semaphore.h"

class Thread {
public:
    Thread(Buffer& buffer, std::string IP, std::string port);
	virtual ~Thread();
	void start();
    virtual void run() = 0;
	void join();
    void terminate();
	pthread_t getId();


    void error(const char *msg);

    std::string IP_;
    std::string port_;

    Buffer& buffer_;

private:
	pthread_t id;

	static void *staticRun(void *args);
};

#endif /* THREAD_H_ */
