#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    _name=true;
    connect(ui->send, &QPushButton::clicked, this, &Chat::readMsg);
}

Chat::~Chat()
{
    delete ui;
    ui = nullptr;
}

void Chat::cleanUp()
{
    ui->read->clear();
    close();
}

void Chat::readMsg()
{
    QString msg=ui->write->toPlainText();
    ui->read->append(_Name + " : " + msg);
    ui->read->append("===========================");
    emit writeMsg(msg, false);
    ui->write->clear();
}

void Chat::nameOpp(QString nameOpp)
{
    _nameOpp=nameOpp;
}

void Chat::chat(QString msg)
{
    ui->read->append(_nameOpp + " : "  + msg);
    ui->read->append("===========================");
}

