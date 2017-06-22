/*
 * Thread.cpp
 *
 *  Created on: 16 de abr de 2017
 *      Author: Suporte
 */

#include "Thread.h"
#include <iostream>


Thread::Thread(Buffer &buffer, std::string IP, std::string port):
buffer_(buffer),
IP_(IP),
port_(port)
{}

Thread::~Thread() {}

void Thread::start() {
	pthread_create(&id, NULL, staticRun, this);
}

void Thread::join() {
	pthread_join(id, NULL);
}

pthread_t Thread::getId() {
	return id;
}

void Thread::terminate(){
    pthread_exit(0);
}

void *Thread::staticRun(void *args) {
	Thread *t = (Thread*) args;

	t->run();

	return NULL;
}

void Thread::error(const char *msg){
    perror(msg);
    exit(0);
}


