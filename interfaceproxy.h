#ifndef INTERFACEPROXY_H
#define INTERFACEPROXY_H
#include "Thread.h"
#include "server.h"
#include "client.h"
#include "buffer.h"
#include <QString>
#include <QDebug>
#include <QMainWindow>

namespace Ui {
class InterfaceProxy;
}

class InterfaceProxy : public QMainWindow
{
    Q_OBJECT

public:

    typedef struct client_struct{
        client_struct(Client* client_ptr, unsigned int id):client_ptr(client_ptr), id(id){}
        Client* client_ptr;
        unsigned int id;
    } client_struct;

    explicit InterfaceProxy(QWidget *parent = 0);
    ~InterfaceProxy();

private slots:
    void on_play_servidor_clicked();

    void on_play_cliente1_clicked();

    void on_play_cliente2_clicked();

    void on_play_cliente3_clicked();

    void on_play_cliente4_clicked();

    void on_play_cliente5_clicked();

    void on_play_cliente6_clicked();

    void on_play_cliente7_clicked();

    void on_stop_cliente1_clicked();

    void on_stop_cliente2_clicked();

    void on_stop_cliente3_clicked();

    void on_stop_cliente4_clicked();

    void on_stop_cliente5_clicked();

    void on_stop_cliente6_clicked();

    void on_stop_cliente7_clicked();

private:
    Ui::InterfaceProxy *ui;

    std::vector<client_struct> clients;
};

#endif // INTERFACEPROXY_H
