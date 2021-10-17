#include "network.h"
#include <iostream>
#include <QString>
#include <QDebug>
Network::Network(QWidget *parent): QObject(parent)
{
}

void Network::setUp(QPushButton *start, QPushButton *quit, QRadioButton *server, QRadioButton *client, QRadioButton *youBegin, QRadioButton *opponentBegins, QLineEdit *ip, QLineEdit *port, QLineEdit *group, QRadioButton *randomBeginner, QRadioButton *animalTexture, QLineEdit *name)
{
    _name=name;
    _animalTexture=animalTexture;
    _animalTexture->setChecked(true);
    _randomBeginner=randomBeginner;
    _start=start;
    _group=group;
    _quit=quit;
    _server=server;
    _client=client;
    _youBegin=youBegin;
    _opponentBegins=opponentBegins;
    _ip=ip;
    _port=port;
    _group->setDisabled(true);
    _youBegin->setDisabled(true);
    _opponentBegins->setDisabled(true);
    _port->setDisabled(true);
    _ip->setDisabled(true);
    _start->setDisabled(true);
    _randomBeginner->setDisabled(true);
    connect(_server, &QRadioButton::pressed, this, &Network::serverMode);
    connect(_client, &QRadioButton::pressed, this, &Network::clientMode);
    connect(_start, &QPushButton::clicked, this, &Network::start);
    qDebug()<<"---------------------------++++++++++";
}

void Network::serverMode()
{
    qDebug() << "--------------";
    _ip->clear();
    _ip->setDisabled(true);
    _port->setEnabled(true);
    _youBegin->setEnabled(true);
    _opponentBegins->setEnabled(true);
    _start->setEnabled(true);
    _randomBeginner->setEnabled(true);
    //_group->setEnabled(true);
}

void Network::clientMode()
{
    _ip->setEnabled(true);
    _port->setEnabled(true);
    _youBegin->setDisabled(true);
    _opponentBegins->setDisabled(true);
    _start->setEnabled(true);
    _randomBeginner->setDisabled(true);
    //_group->setEnabled(true);
}

void Network::start()
{
    int beginnender;
    bool worked;
    QString name=_name->text();
    //int group=_group->text().toUInt(&worked);
    if(_port->text().toUInt(&worked)==0){
        //emit clientSetup(0, "", false, false);
    }else{
    port=_port->text().toShort(&worked);
    ip=_ip->text();
    if(_server->isChecked()){
        isServer=true;
    }else{
        isServer=false;
    }
    if(_youBegin->isChecked()&&!_opponentBegins->isChecked()&&!_randomBeginner->isChecked()){
        begins=true;
        beginnender = 0;
    }else if(!_youBegin->isChecked()&&_opponentBegins->isChecked()&&!_randomBeginner->isChecked()){
        begins=false;
        beginnender = 1;
    }else{
        //quint32 rng=QRandomGenerator::global()->generate();
        quint32 rng=static_cast<quint32>(rand());
        begins=rng%2;
        beginnender=!begins;
    }
    if(isServer&&port!=0){
    emit serverSetup(port, beginnender, ip, isServer,name);
    }else if(port!=0&&ip!=""){
    emit clientSetup(port, ip, isServer, begins,name);
    }
    }
}


