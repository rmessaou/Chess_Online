#include "myserver.h"

MyServer::MyServer(quint16 port, quint8 beginnender, QObject *parent) :
    QObject(parent), _port(port), _beginnender(beginnender)
{

    qDebug() << "I m here server";
    server=new QTcpServer(this);
    socket = new QTcpSocket(this);
    stream.setDevice(socket);
    connect(server, &QTcpServer::newConnection, this, &MyServer::sessionOpen);
//    connect(socket, &QTcpSocket::disconnected, this, &MyServer::connetionError);
    if(!server->listen(QHostAddress::Any, port)){
        qDebug() << " errrrroor " ;
    }else
        qDebug() << " server started" ;
}

void MyServer::sessionOpen(){
    qDebug() << "clients " << clients;
    if(clients < 1){
    clients++;
    socket = server->nextPendingConnection();
    socket->open(QIODevice::ReadWrite);
    stream.setDevice(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MyServer::sendData);
    connect(socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &MyServer::connetionError);
}else {
        qDebug() << "another one tried to connect";
        server -> close();
        return;
    }
}

void MyServer::sendData(){
    qDebug() << "Server is reading data from client .." ;
    quint8 byte0;
    stream >> byte0; //erstes Byte
    std::vector<quint8> vector;
        switch (byte0)
        {
        case(0x02) :{
            quint8 length;
            stream >> length;
            stream >> gegnernummer;
            qDebug() << "recieved log in from client " << 0x02 << " " << length << " " << gegnernummer;
            endSignIn();
            emit startInfo(we, _beginnender, gegnernummer);
        }
            break;
        case(0x03) : {
            quint8 length; //um das erste Byte zu entfernen
            quint8 letztesbyte;
            stream>> length;
            for(int i=0; i<4; i++){
                quint8 tmp;
                stream >> tmp;
                vector.push_back(tmp);
            qDebug() << "recieved move" << tmp;
            }
            stream >> letztesbyte;
            int b = letztesbyte >> 4;
            int a = letztesbyte & 0x0F;
            qDebug() << "recieved move" << a;
            qDebug() << "recieved move" << b;
            emit sendVector(vector[0],vector[1],vector[2],vector[3],a, b);
        } break;

        case (0x04) : {
            quint8 length; //um das erste Byte zu entfernen
            stream>> length;
            quint8 tmp;
            stream>>tmp;
            qDebug() << "recieved response" << 0x04 << " " << length << " " << tmp;
            emit responseToMove(tmp);
        }
            break;
        case(0xFF) : {
            quint8 length;
            stream >> length;
            emit aufgeben();
            qDebug()<< "--------------SURRENDER---------";
        } break;

        case(0xF5):{
            quint8 length;
            stream >> length;
            emit remi();
            qDebug() << "remiiiiiiiiiiiiiii";
        }
            break;

        case 0xF6:{
            quint8 length,antwort;
            stream >> length;
            stream >> antwort;
            if(antwort == 0x00){
                qDebug() << "reeeeeeeeeeeeeeeemmmmmmmmmmmmmmmmmmmmmmath";
                emit okRematch();
            }
            else if(antwort == 0x01){
                qDebug() << "recieveeeeeed no rematch !!!&&&&&&&&&&&&";
                emit noRematch();
                lostConnexion();
            }
            else{
                qDebug() << "recieved false disconnect msg";
                lostConnexion();
            }
        }
            break;

        case (0xF7) : {
            qDebug() << "recieved messsage";
            quint8 lenght;
            QString nachricht;
            stream >> lenght;
            stream >> nachricht;
            qDebug() << "recieved " << nachricht;
            emit chat(nachricht);
        } break;

        case (0xF8) : {
            qDebug() << "recieved name";
            quint8 length;
            QString name;
            stream >> length;
            stream >> name;
            emit sendName(name);
        } break;

        default:
            qDebug()<<"etwas ist schiefgelaufen. recieved false byte from client" << (byte0 >> 4) << " " << (byte0 & 0x0F);
            disconnect();
    }
}

void MyServer::writeData(std::vector<quint8> movevector){
    stream.setDevice(socket);
    qDebug() <<" write data to client";
    for(auto i: movevector){
        stream << i;
        }
    socket->flush();
}

void MyServer::endSignIn(){
    stream.setDevice(socket);
    quint8 cmd = 0x01;
    quint8 length = 0x02;
    stream << cmd << length << _beginnender << gruppennummer;
    socket->flush();

    qDebug() << "sendin sign in infos";

}

void MyServer::rematch(){
    std::vector<quint8> remis;
    remis.push_back(0xF5);
    remis.push_back(0x00);
    writeData(remis);
}

void MyServer::writeOkRematch(){
    quint8 cmd = 0xF6, length = 0x01, value = 0x00;
    stream<<cmd<<length<<value;
}

void MyServer::writeNoRematch(){
    quint8 cmd = 0xF6, length = 0x01, value = 0x01;
    stream<<cmd<<length<<value;
    socket->flush();
    disconnect();
}

void MyServer::writeMessage(QString msg, bool name){
    stream.setDevice(socket);
    quint8 cmd;
    if(!name)
        cmd = 0xF7;
    else
        cmd = 0xF8;
    quint8 length = 0x01;
    stream << cmd << length << msg;
    socket->flush();
    qDebug() << "wrote msg : " << msg;

}

void MyServer::disconnect(){
    qDebug() << "server disconnected";
    socket->disconnectFromHost();
    server->close();
    clients = 0;
//    emit serverDisconnect();
}

void MyServer::recieveName(QString name){
    qDebug() << "HI I AM HERE BEFORE: " << _name;
    _name = name;
    qDebug() << "HI I AM HERE NEXT: " << _name;
}

void MyServer::writeName(){
    if(sendname){
        qDebug() << "server wrote" << _name;
        writeMessage(_name,true);
        socket->flush();
}
}

void MyServer::connetionError(){
    qDebug() << "server disconnected";
    socket->disconnectFromHost();
    server->close();
    clients = 0;
    emit lostConnexion();
}
