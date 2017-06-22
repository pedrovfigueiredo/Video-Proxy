#include "client.h"
#include <vector>
#include <QDebug>

Client::Client(Buffer &buffer, std::string IP, std::string port):
    Thread::Thread{buffer, IP, port}
{
    sem_stopped = new Semaphore(0);
}

Client::~Client(){

}

void Client::run(){

    buildSocket();

    while(true){

        //Protocolo de Entrada do Leitor / Escritor

        buffer_.mutexF->P();

            if(priorityLevel == priority::High){ // High Priority

                if(buffer_.nhighP > 0 || buffer_.nlowP > 0){
                    buffer_.dhighP++;
                    buffer_.mutexF->V();
                    buffer_.highP->P();
                }

                buffer_.nhighP++;

            }else{ // Low Priority

                if(buffer_.nhighP > 0){
                    buffer_.dlowP++;
                    buffer_.mutexF->V();
                    buffer_.lowP->P();
                }

                buffer_.nlowP++;
            }

            buffer_.numActiveThreads++;

        buffer_.mutexF->V();


        while (true) {

            buffer_.mutexF->P();
            if (!buffer_.consumersCount){
                buffer_.full->P();  // Protocolo de Entrada Buffers Limitados
            }

            // Incrementa o número de consumidores
            buffer_.consumersCount++;

            readBuffer();

            localFront = (localFront + 1) % BUFFER_SIZE;

            // Zera count
            if(buffer_.consumersCount >= buffer_.numActiveThreads){
                buffer_.consumersCount = 0;
                buffer_.empty->V(); // Protocolo de Saída Buffers Limitados
            }

            buffer_.mutexF->V();

            streamVideo();

            if(stopped) {
                buffer_.mutexF->P();
                buffer_.numActiveThreads--;
                buffer_.mutexF->V();
                break;
            }

        }

        //Protocolo de Saída do Leitor / Escritor

        buffer_.mutexF->P();

            if(priorityLevel == priority::High){ // High Priority
                buffer_.nhighP--;

                /****  Signal  ****/

                if( buffer_.dhighP > 0){
                    buffer_.dhighP--;
                    buffer_.highP->V();
                }else{
                    while(buffer_.dlowP > 0){
                        buffer_.dlowP--;
                        buffer_.lowP->V();
                    }
                }

            }else{ // Low Priority
                buffer_.nlowP--;

                /****  Signal  ****/

                if(buffer_.nlowP == 0 && buffer_.dhighP > 0){
                    buffer_.dhighP--;
                    buffer_.highP->V();
                }

             }

            buffer_.mutexF->V();


            sem_stopped->P();

        }

}


void Client::readBuffer(){

    //Ler dados do buffer
    for(int i = 0; i < DATA_SIZE; i++)
        localFrame[i] = buffer_.data[localFront].frame[i];


}

void Client::streamVideo(){
    int n;
    // Envia dados pela rede. Parametros: socket, buffer que contem os dados,
    // tamanho do buffer, flags, endereco da maquina destino, tamanho da estrutura do endereco.
    // Retorna o numero de bytes enviados.

    n = sendto(sock, localFrame, DATA_SIZE, 0, (const struct sockaddr *) &server, length);

    if (n < 0) error("Sendto");
}

void Client::buildSocket(){
    // Cria um socket do tipo datagrama e retorna um descritor
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0) error("socket");

    // Define a familia do endereco como do tipo Internet
    server.sin_family = AF_INET;

    // Preenche a estrutura "hp" a partir do nome da maquina ou de seu IP
    hp = gethostbyname(IP_.c_str());

    if (hp == 0) error("Unknown host");

    // Copia o IP da estrutura "hp" para a estrutura "server"
    bcopy( (char *) hp->h_addr, (char *) &server.sin_addr, hp->h_length);
    // A funcao htons() converte o numero da porta para o padrao Little Endian.
    server.sin_port = htons(atoi(port_.c_str()));

    length = sizeof(struct sockaddr_in);

}

void Client::stop(){
    stopped = true;
}

void Client::resume(){
    stopped = false;
    sem_stopped->V();
}
