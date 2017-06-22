#include "interfaceproxy.h"
#include "ui_interfaceproxy.h"
#include <QPainter>
#include <QPalette>


Buffer limited_buffer;

InterfaceProxy::InterfaceProxy(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterfaceProxy)
{
    ui->setupUi(this);

    /***** Background *****/

    QPixmap backgnd("://Background.jpg");

    QPalette palette;
    palette.setBrush(QPalette::Background, backgnd);
    this->setPalette(palette);

    //resize(imagem.size());
    //InterfaceProxy::showMaximized();

    /*********************/

    ui->Servidor->setStyleSheet("QLabel {color : white; }");
    ui->IP_Servidor->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Servidor->setStyleSheet("QLabel {color : white; }");

    ui->Cliente_1->setStyleSheet("QLabel {color : white; }");
    ui->IP_Cliente_1->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Cliente_1->setStyleSheet("QLabel {color : white; }");
    ui->checkBox_cliente_1->setStyleSheet("QCheckBox {color : white; }");

    ui->Cliente_2->setStyleSheet("QLabel {color : white; }");
    ui->IP_Cliente_2->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Cliente_2->setStyleSheet("QLabel {color : white; }");
    ui->checkBox_cliente_2->setStyleSheet("QCheckBox {color : white; }");

    ui->Cliente_3->setStyleSheet("QLabel {color : white; }");
    ui->IP_Cliente_3->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Cliente_3->setStyleSheet("QLabel {color : white; }");
    ui->checkBox_cliente_3->setStyleSheet("QCheckBox {color : white; }");

    ui->Cliente_4->setStyleSheet("QLabel {color : white; }");
    ui->IP_Cliente_4->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Cliente_4->setStyleSheet("QLabel {color : white; }");
    ui->checkBox_cliente_4->setStyleSheet("QCheckBox {color : white; }");

    ui->Cliente_5->setStyleSheet("QLabel {color : white; }");
    ui->IP_Cliente_5->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Cliente_5->setStyleSheet("QLabel {color : white; }");
    ui->checkBox_cliente_5->setStyleSheet("QCheckBox {color : white; }");

    ui->Cliente_6->setStyleSheet("QLabel {color : white; }");
    ui->IP_Cliente_6->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Cliente_6->setStyleSheet("QLabel {color : white; }");
    ui->checkBox_cliente_6->setStyleSheet("QCheckBox {color : white; }");

    ui->Cliente_7->setStyleSheet("QLabel {color : white; }");
    ui->IP_Cliente_7->setStyleSheet("QLabel {color : white; }");
    ui->Porta_Cliente_7->setStyleSheet("QLabel {color : white; }");
    ui->checkBox_cliente_7->setStyleSheet("QCheckBox {color : white; }");

    ui->play_cliente1->setDisabled(true);
    ui->play_cliente2->setDisabled(true);
    ui->play_cliente3->setDisabled(true);
    ui->play_cliente4->setDisabled(true);
    ui->play_cliente5->setDisabled(true);
    ui->play_cliente6->setDisabled(true);
    ui->play_cliente7->setDisabled(true);

    ui->stop_cliente1->setDisabled(true);
    ui->stop_cliente2->setDisabled(true);
    ui->stop_cliente3->setDisabled(true);
    ui->stop_cliente4->setDisabled(true);
    ui->stop_cliente5->setDisabled(true);
    ui->stop_cliente6->setDisabled(true);
    ui->stop_cliente7->setDisabled(true);

    ui->checkBox_cliente_1->setDisabled(true);
    ui->checkBox_cliente_2->setDisabled(true);
    ui->checkBox_cliente_3->setDisabled(true);
    ui->checkBox_cliente_4->setDisabled(true);
    ui->checkBox_cliente_5->setDisabled(true);
    ui->checkBox_cliente_6->setDisabled(true);
    ui->checkBox_cliente_7->setDisabled(true);

}

InterfaceProxy::~InterfaceProxy()
{
    delete ui;
}

void InterfaceProxy::on_play_servidor_clicked()
{
    QString IP_Server = ui->lineEdit_Servidor_IP->text();
    QString Port_Server = ui->lineEdit_Servidor_Port->text();

    Server* server;

    server = new Server(limited_buffer, IP_Server.toUtf8().constData(), Port_Server.toUtf8().constData());

    server->start();

    ui->play_servidor->setDisabled(true);

    ui->play_cliente1->setDisabled(false);
    ui->play_cliente2->setDisabled(false);
    ui->play_cliente3->setDisabled(false);
    ui->play_cliente4->setDisabled(false);
    ui->play_cliente5->setDisabled(false);
    ui->play_cliente6->setDisabled(false);
    ui->play_cliente7->setDisabled(false);

    ui->checkBox_cliente_1->setDisabled(false);
    ui->checkBox_cliente_2->setDisabled(false);
    ui->checkBox_cliente_3->setDisabled(false);
    ui->checkBox_cliente_4->setDisabled(false);
    ui->checkBox_cliente_5->setDisabled(false);
    ui->checkBox_cliente_6->setDisabled(false);
    ui->checkBox_cliente_7->setDisabled(false);

    ui->lineEdit_Servidor_IP->setDisabled(true);
    ui->lineEdit_Servidor_Port->setDisabled(true);
}

void InterfaceProxy::on_play_cliente1_clicked()
{

    ui->lineEdit_Cliente_1_IP->setDisabled(true);
    ui->lineEdit_Cliente_1_Port->setDisabled(true);
    ui->checkBox_cliente_1->setDisabled(true);
    ui->stop_cliente1->setDisabled(false);
    ui->play_cliente1->setDisabled(true);

    QString IP_Client1 = ui->lineEdit_Cliente_1_IP->text();
    QString Port_Client1 = ui->lineEdit_Cliente_1_Port->text();

    for(size_t i = 0; i < clients.size(); i++){

        // Resume if there's an active client thread

        if(clients[i].id == 1){

            if(ui->checkBox_cliente_1->isChecked())
                clients[i].client_ptr->priorityLevel = Client::priority::High;
            else
                clients[i].client_ptr->priorityLevel = Client::priority::Low;

           clients[i].client_ptr->resume();

           return;
        }
    }

    clients.push_back({new Client(limited_buffer, IP_Client1.toUtf8().constData(), Port_Client1.toUtf8().constData()), 1});

    if(ui->checkBox_cliente_1->isChecked())
        clients.back().client_ptr->priorityLevel = Client::priority::High;

    clients.back().client_ptr->start();

}

void InterfaceProxy::on_play_cliente2_clicked()
{

    ui->lineEdit_Cliente_2_IP->setDisabled(true);
    ui->lineEdit_Cliente_2_Port->setDisabled(true);
    ui->checkBox_cliente_2->setDisabled(true);
    ui->stop_cliente2->setDisabled(false);
    ui->play_cliente2->setDisabled(true);


    QString IP_Client2 = ui->lineEdit_Cliente_2_IP->text();
    QString Port_Client2 = ui->lineEdit_Cliente_2_Port->text();

    for(size_t i = 0; i < clients.size(); i++){

        // Resume if there's an active client thread

        if(clients[i].id == 2){

            if(ui->checkBox_cliente_2->isChecked())
                clients[i].client_ptr->priorityLevel = Client::priority::High;
            else
                clients[i].client_ptr->priorityLevel = Client::priority::Low;

           clients[i].client_ptr->resume();

           return;
        }
    }

    clients.push_back({new Client(limited_buffer, IP_Client2.toUtf8().constData(), Port_Client2.toUtf8().constData()), 2});

    if(ui->checkBox_cliente_2->isChecked())
        clients.back().client_ptr->priorityLevel = Client::priority::High;

    clients.back().client_ptr->start();
}

void InterfaceProxy::on_play_cliente3_clicked()
{

    ui->lineEdit_Cliente_3_IP->setDisabled(true);
    ui->lineEdit_Cliente_3_Port->setDisabled(true);
    ui->checkBox_cliente_3->setDisabled(true);
    ui->stop_cliente3->setDisabled(false);
    ui->play_cliente3->setDisabled(true);


    QString IP_Client3 = ui->lineEdit_Cliente_3_IP->text();
    QString Port_Client3 = ui->lineEdit_Cliente_3_Port->text();


    for(size_t i = 0; i < clients.size(); i++){

        // Resume if there's an active client thread

        if(clients[i].id == 3){

            if(ui->checkBox_cliente_3->isChecked())
                clients[i].client_ptr->priorityLevel = Client::priority::High;
            else
                clients[i].client_ptr->priorityLevel = Client::priority::Low;

           clients[i].client_ptr->resume();

           return;
        }
    }

    clients.push_back({new Client(limited_buffer, IP_Client3.toUtf8().constData(), Port_Client3.toUtf8().constData()), 3});

    if(ui->checkBox_cliente_3->isChecked())
        clients.back().client_ptr->priorityLevel = Client::priority::High;

    clients.back().client_ptr->start();
}

void InterfaceProxy::on_play_cliente4_clicked()
{

    ui->lineEdit_Cliente_4_IP->setDisabled(true);
    ui->lineEdit_Cliente_4_Port->setDisabled(true);
    ui->checkBox_cliente_4->setDisabled(true);
    ui->stop_cliente4->setDisabled(false);
    ui->play_cliente4->setDisabled(true);

    QString IP_Client4 = ui->lineEdit_Cliente_4_IP->text();
    QString Port_Client4 = ui->lineEdit_Cliente_4_Port->text();

    for(size_t i = 0; i < clients.size(); i++){

        // Resume if there's an active client thread

        if(clients[i].id == 4){

            if(ui->checkBox_cliente_4->isChecked())
                clients[i].client_ptr->priorityLevel = Client::priority::High;
            else
                clients[i].client_ptr->priorityLevel = Client::priority::Low;

           clients[i].client_ptr->resume();

           return;
        }
    }

    clients.push_back({new Client(limited_buffer, IP_Client4.toUtf8().constData(), Port_Client4.toUtf8().constData()), 4});

    if(ui->checkBox_cliente_4->isChecked())
        clients.back().client_ptr->priorityLevel = Client::priority::High;

    clients.back().client_ptr->start();
}

void InterfaceProxy::on_play_cliente5_clicked()
{

    ui->lineEdit_Cliente_5_IP->setDisabled(true);
    ui->lineEdit_Cliente_5_Port->setDisabled(true);
    ui->checkBox_cliente_5->setDisabled(true);
    ui->stop_cliente5->setDisabled(false);
    ui->play_cliente5->setDisabled(true);

    QString IP_Client5 = ui->lineEdit_Cliente_5_IP->text();
    QString Port_Client5 = ui->lineEdit_Cliente_5_Port->text();

    for(size_t i = 0; i < clients.size(); i++){

        // Resume if there's an active client thread

        if(clients[i].id == 5){

            if(ui->checkBox_cliente_5->isChecked())
                clients[i].client_ptr->priorityLevel = Client::priority::High;
            else
                clients[i].client_ptr->priorityLevel = Client::priority::Low;

           clients[i].client_ptr->resume();

           return;
        }
    }

    clients.push_back({new Client(limited_buffer, IP_Client5.toUtf8().constData(), Port_Client5.toUtf8().constData()), 5});

    if(ui->checkBox_cliente_5->isChecked())
        clients.back().client_ptr->priorityLevel = Client::priority::High;

    clients.back().client_ptr->start();
}

void InterfaceProxy::on_play_cliente6_clicked()
{

    ui->lineEdit_Cliente_6_IP->setDisabled(true);
    ui->lineEdit_Cliente_6_Port->setDisabled(true);
    ui->checkBox_cliente_6->setDisabled(true);
    ui->stop_cliente6->setDisabled(false);
    ui->play_cliente6->setDisabled(true);

    QString IP_Client6 = ui->lineEdit_Cliente_6_IP->text();
    QString Port_Client6 = ui->lineEdit_Cliente_6_Port->text();

    for(size_t i = 0; i < clients.size(); i++){

        // Resume if there's an active client thread

        if(clients[i].id == 6){

            if(ui->checkBox_cliente_6->isChecked())
                clients[i].client_ptr->priorityLevel = Client::priority::High;
            else
                clients[i].client_ptr->priorityLevel = Client::priority::Low;

           clients[i].client_ptr->resume();

           return;
        }
    }

    clients.push_back({new Client(limited_buffer, IP_Client6.toUtf8().constData(), Port_Client6.toUtf8().constData()), 6});

    if(ui->checkBox_cliente_6->isChecked())
        clients.back().client_ptr->priorityLevel = Client::priority::High;

    clients.back().client_ptr->start();
}

void InterfaceProxy::on_play_cliente7_clicked()
{

    ui->lineEdit_Cliente_7_IP->setDisabled(true);
    ui->lineEdit_Cliente_7_Port->setDisabled(true);
    ui->checkBox_cliente_7->setDisabled(true);
    ui->stop_cliente7->setDisabled(false);
    ui->play_cliente7->setDisabled(true);

    QString IP_Client7 = ui->lineEdit_Cliente_7_IP->text();
    QString Port_Client7 = ui->lineEdit_Cliente_7_Port->text();

    for(size_t i = 0; i < clients.size(); i++){

        // Resume if there's an active client thread

        if(clients[i].id == 7){

            if(ui->checkBox_cliente_7->isChecked())
                clients[i].client_ptr->priorityLevel = Client::priority::High;
            else
                clients[i].client_ptr->priorityLevel = Client::priority::Low;

           clients[i].client_ptr->resume();

           return;
        }
    }

    clients.push_back({new Client(limited_buffer, IP_Client7.toUtf8().constData(), Port_Client7.toUtf8().constData()), 7});

    if(ui->checkBox_cliente_7->isChecked())
        clients.back().client_ptr->priorityLevel = Client::priority::High;

    clients.back().client_ptr->start();
}

void InterfaceProxy::on_stop_cliente1_clicked()
{
    for(auto&&client_s : clients){
        if(client_s.id == 1){
            client_s.client_ptr->stop();
            ui->checkBox_cliente_1->setDisabled(false);
            ui->stop_cliente1->setDisabled(true);
            ui->play_cliente1->setDisabled(false);
        }
    }
}

void InterfaceProxy::on_stop_cliente2_clicked()
{
    for(auto&&client_s : clients){
        if(client_s.id == 2){
            client_s.client_ptr->stop();
            ui->checkBox_cliente_2->setDisabled(false);
            ui->stop_cliente2->setDisabled(true);
            ui->play_cliente2->setDisabled(false);
        }
    }
}

void InterfaceProxy::on_stop_cliente3_clicked()
{
    for(auto&&client_s : clients){
        if(client_s.id == 3){
            client_s.client_ptr->stop();
            ui->checkBox_cliente_3->setDisabled(false);
            ui->stop_cliente3->setDisabled(true);
            ui->play_cliente3->setDisabled(false);
        }
    }
}

void InterfaceProxy::on_stop_cliente4_clicked()
{
    for(auto&&client_s : clients){
        if(client_s.id == 4){
            client_s.client_ptr->stop();
            ui->checkBox_cliente_4->setDisabled(false);
            ui->stop_cliente4->setDisabled(true);
            ui->play_cliente4->setDisabled(false);
        }
    }
}

void InterfaceProxy::on_stop_cliente5_clicked()
{
    for(auto&&client_s : clients){
        if(client_s.id == 5){
            client_s.client_ptr->stop();
            ui->checkBox_cliente_5->setDisabled(false);
            ui->stop_cliente5->setDisabled(true);
            ui->play_cliente5->setDisabled(false);
        }
    }
}

void InterfaceProxy::on_stop_cliente6_clicked()
{
    for(auto&&client_s : clients){
        if(client_s.id == 6){
            client_s.client_ptr->stop();
            ui->checkBox_cliente_6->setDisabled(false);
            ui->stop_cliente6->setDisabled(true);
            ui->play_cliente6->setDisabled(false);
        }
    }
}

void InterfaceProxy::on_stop_cliente7_clicked()
{
    for(auto&&client_s : clients){
        if(client_s.id == 7){
            client_s.client_ptr->stop();
            ui->checkBox_cliente_7->setDisabled(false);
            ui->stop_cliente7->setDisabled(true);
            ui->play_cliente7->setDisabled(false);
        }
    }
}
