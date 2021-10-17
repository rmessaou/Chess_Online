#include "errormessage.h"
#include "ui_errormessage.h"

ErrorMessage::ErrorMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessage)
{
    ui->setupUi(this);
    connect(ui->backToMain, &QPushButton::clicked, this, &ErrorMessage::close);
    ui->errorText->setDisabled(true);
}

ErrorMessage::~ErrorMessage()
{
    delete ui;
    ui = nullptr;
}
