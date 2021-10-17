#include "myclient.h"

MyClient::MyClient(QString _host, quint16 _port, QObject* parent):QObject(parent),
    host(_host),port(_port)
{
    socket = new QTcpSocket(this);
    qDebug() << "Hi I am client const";
    connectToServer();
    stream.setDevice(socket);
    connect(socket, &QTcpSocket::connected, this, &MyClient::signIn);
    connect(socket, &QTcpSocket::readyRead, this, &MyClient::readData);
    connect(socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &MyClient::connetionError);
//    connect(socket, &QTcpSocket::disconnected, this, &MyClient::disconnect);
}

void MyClient::connectToServer(){
        socket->connectToHost(host, port);
        if (socket->waitForConnected(1000)){
            qDebug() << "Connected!";
            signIn();

        }
        else{
            qDebug() << "error in connection";
            disconnect();
        }

}

void MyClient::readData(){
    quint8 byte0;
    stream >> byte0; //erstes Byte
    std::vector<quint8> vector;

        switch (byte0)
        {
            case (0x01) :{
                quint8 length; //um das erste Byte zu entfernen
                stream>> length;
                for(int i=0 ; i<2; i++){
                    quint8 tmp;
                    stream >> tmp; //beginnender zuerst
                    vector.push_back(tmp);
                }
                qDebug() << "recieved log info from server " << 0x01 << " " << length << " " << vector[0] << " " << vector[1];
                emit startInfo(wir, vector[0], vector[1]); // what we are .. who begins
        }
            break;

        case(0x03) : {
            quint8 lenght; //um das erste Byte zu entfernen
            quint8 letztesbyte;
            stream>> lenght;
            for(int i=0; i<4; i++){
                quint8 tmp;
                stream >> tmp;
                vector.push_back(tmp);
                qDebug() << "recieved from server" << tmp;
            }
            stream >> letztesbyte;
            int b = letztesbyte >> 4;
            int a = letztesbyte & 0x0F;
            qDebug() << "recieved from server" << a;
            qDebug() << "recieved from server" << b;
            emit sendVector(vector[0],vector[1],vector[2],vector[3],a, b); // status first(digit on the right) .. then umwandlung (digit on left)
        } break;

        case (0x04) : {
            quint8 lenght; //um das erste Byte zu entfernen
            stream>> lenght;
            quint8 tmp;
            stream>>tmp;
            emit responseToMove(tmp);
        }
            break;
        case(0x00):
            qDebug() << "why 0";
            break;

        case(0xFF) : {
            quint8 length;
            stream >> length;
            emit aufgeben();
            qDebug()<<"+++++++++++++++++SURRENDER++++++++++++";
        } break;
        case(0xF5):{
            quint8 length;
            stream >> length;
            emit remi();
            qDebug() << "remiiiiiiiiiiiiiii";
        }
            break;
        case (0xF6):{
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
                qDebug() << "recieved false antwort for rematch";
                lostConnexion();
            }
        }
            break;

        case (0xF7) : {
            quint8 lenght;
            QString nachricht;
            stream >> lenght;
            stream >> nachricht;
            emit chat(nachricht);
            qDebug() << "recieved " << nachricht;
        } break;

        case (0xF8) : {
            quint8 length;
            QString name;
            stream >> length;
            stream >> name;
            emit sendName(name);
        } break;

        default:
            qDebug()<< byte0;
            qDebug()<<"etwas ist schiefgelaufen. recieved false byte from server";
            disconnect();
            break;
    }
}

void MyClient::writeData(std::vector<quint8> movevector){
    qDebug() <<" write data to server";
    for(auto i: movevector){
        stream << i;
        }
    socket->flush();
    qDebug() <<" finisheds";
}

void MyClient::signIn(){
    qDebug() << "writing sign in to server";
    stream.setDevice(socket);
    std::vector<quint8> p;
    quint8 signIn = 0x02;
    quint8 length = 0x01;
    stream << signIn << length << gruppennummer;
    socket->flush();
}

void MyClient::rematch(){
    std::vector<quint8> remis;
    remis.push_back(0xF5);
    remis.push_back(0x00);
    writeData(remis);
}

void MyClient::writeOkRematch(){
    quint8 cmd = 0xF6, length = 0x01, value = 0x00;
    stream<<cmd<<length<<value;
}

void MyClient::writeNoRematch(){
    quint8 cmd = 0xF6, length = 0x01, value = 0x01;
    stream<<cmd<<length<<value;
    socket->flush();
    disconnect();
}

void MyClient::writeMessage(QString msg, bool name){
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

void MyClient::disconnect(){
    qDebug() << "client disconnected";
    socket->disconnectFromHost();
}

void MyClient::recieveName(QString name){
    qDebug() << "HI I AM HERE BEFORE: " << _name;
    _name = name;
    qDebug() << "HI I AM HERE NEXT: " << _name;
}

void MyClient::writeName(){
    if(sendname){
        qDebug() << "client wrote" << _name;
        writeMessage(_name,true);
        socket->flush();
}
}

void MyClient::connetionError(){
    qDebug() << "server disconnected";
    socket->disconnectFromHost();
    emit lostConnexion();
}
