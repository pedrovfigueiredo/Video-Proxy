#include "server.h"
#include <vector>
#include <QDebug>
Server::Server(Buffer &buffer, std::string IP, std::string port):
    Thread::Thread{buffer, IP, port}
{}

Server::~Server(){}

void Server::run(){

    buildSocket();

    qDebug() << "Criou o server";

    while(true){

        receivePackages();

        buffer_.empty->P();
            populateBuffer();
        buffer_.full->V();
    }
}

void Server::receivePackages(){
    int n;

    n = recvfrom(sock, localFrame, DATA_SIZE, 0, (struct sockaddr *) &from, &fromlen);

    if(n < 0) error("Receive");
}

void Server::populateBuffer(){

    //Escrever dados do buffer
    for(int i = 0; i < DATA_SIZE; i++)
        buffer_.data[rear].frame[i] = localFrame[i];

    rear = (rear + 1) % BUFFER_SIZE;

}

void Server::buildSocket(){
// Cria um socket do tipo datagrama e retorna um descritor
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) error("Opening socket");

    length = sizeof(server);

    // Zera a estrutura "server"
    bzero(&server, length);
    // Define a familia do endereco como do tipo Internet
    server.sin_family = AF_INET;

    // Seta o endereco para localhost (127.0.0.1)
    server.sin_addr.s_addr = inet_addr(IP_.c_str());
    // A funcao htons() converte o numero da porta para o padrao Little Endian.
    server.sin_port = htons(atoi(port_.c_str()));

    // Associa um socket a um endereco
    if (bind(sock, (struct sockaddr *) &server, length) < 0)
        error("binding");

    fromlen = sizeof(struct sockaddr_in);
}
