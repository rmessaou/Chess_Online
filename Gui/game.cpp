#include "game.h"
#include "ui_game.h"
#include "chesstile.h"
#include "chessboard.h"
#include "chessspace.h"
#include <QMovie>
#include <QDebug>
#include <vector>
#include <QTimer>
#include <QString>
#include <QMessageBox>

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game), _chessBoard(this), _counter(0), _network(this)
{
    ui->setupUi(this);
    //connect(ui->start, &QPushButton::clicked, this, &Game::startGame);
    //ChessBoard _chessBoard(this);
    _network.setUp(ui->start, ui->quit, ui->server, ui->client, ui->youBegin, ui->opponentBegins, ui->ip, ui->port,ui->group, ui->randomBeginner, ui->animalTexture, ui->name);
    //Network _network(ui->start, ui->quit, ui->server, ui->client, ui->whoStarts, ui->ip, ui->port, this);
    qDebug()<<"123456788908";
    _errorMessage=new ErrorMessage(this);
    _chatWindow=new Chat(this);
    _chatWindow->hide();
//    connect(&_network, &Network::clientSetup, this, &Game::startGame);
//    connect(&_network, &Network::serverSetup, this, &Game::startGame);
    _chessBoard.setChoice(ui->choiceLayout/*, ui->choiceWidget*/);
    //connect(ui->end, &QPushButton::clicked, this, &Game::end);
    connect(ui->quit, &QPushButton::clicked, this, &Game::close);
    connect(ui->quit, &QPushButton::clicked, this, &Game::quitGame);
    connect(&_network, &Network::clientSetup, this, &Game::receiveNetworkInfo);
//    connect(&_network, &Network::serverSetup, this, &Game::receiveNetworkInfo);
    //connect(ui->end, &QPushButton::clicked, this, &Game::youWin);
    connect(ui->startWin, &QPushButton::clicked, this, &Game::startWin);
    connect(ui->startWin, &QPushButton::clicked, this, &Game::quitGame);
    connect(ui->startLost, &QPushButton::clicked, this, &Game::startWin);
    connect(ui->startLost, &QPushButton::clicked, this, &Game::quitGame);
    connect(ui->quitWin, &QPushButton::clicked, this, &Game::quitGame);
    connect(ui->quitWin, &QPushButton::clicked, this, &Game::close);
    connect(ui->quitLost, &QPushButton::clicked, this, &Game::quitGame);
    connect(ui->quitLost, &QPushButton::clicked, this, &Game::close);
    connect(ui->menuSurrenderOwn, &QPushButton::clicked, this, &Game::startWin);
    connect(ui->menuSurrenderOwn, &QPushButton::clicked, this, &Game::quitGame);
    connect(ui->menuSurrenderOpp, &QPushButton::clicked, this, &Game::startWin);
    connect(ui->menuSurrenderOpp, &QPushButton::clicked, this, &Game::quitGame);
    connect(ui->quitSurrenderOwn, &QPushButton::clicked, this, &Game::close);
    connect(ui->quitSurrenderOwn, &QPushButton::clicked, this, &Game::quitGame);
    connect(ui->quitSurrenderOpp, &QPushButton::clicked, this, &Game::close);
    connect(ui->quitSurrenderOpp, &QPushButton::clicked, this, &Game::quitGame);
    //connect(ui->errorMessage, &QPushButton::clicked, this, &Game::error);
    connect(ui->rematchWin, &QPushButton::clicked, this, &Game::rematchClicked);
    connect(ui->rematchLoose, &QPushButton::clicked, this, &Game::rematchClicked);
    connect(ui->rematchISurrendered, &QPushButton::clicked, this, &Game::rematchClicked);
    connect(ui->rematchOppSurrendered, &QPushButton::clicked, this, &Game::rematchClicked);
    connect(ui->rematchYes, &QPushButton::clicked, this, &Game::rematchYes);
    connect(ui->rematchNo, &QPushButton::clicked, this, &Game::rematchNo);
    connect(ui->lastSceneWin, &QPushButton::clicked, this, &Game::goBackToLastScene);
    connect(ui->lastSceneLoose, &QPushButton::clicked, this, &Game::goBackToLastScene);
    connect(ui->back, &QPushButton::clicked, this, &Game::back);
    connect(ui->toGame, &QPushButton::clicked, this, &Game::toGame);
    connect(ui->close, &QPushButton::clicked, this, &Game::endIt);
    ui->turnCounterTop->setDisabled(true);
    ui->turnCounterBottom->setDisabled(true);
    ui->timer->setDisabled(true);
    ui->timer->setStyleSheet("color: white");
    _turnCountBottom=0;
    _turnCountTop=0;
    ui->back->hide();
    //ui->stackedWidget->setCurrentIndex(0);//********
    ui->stackedWidget->setCurrentIndex(8);//'''''''''''
    connect(ui->openChat, &QPushButton::clicked, this, &Game::openChat);
    //connect(&_chessBoard, &ChessBoard::bauernumwandlung, this, &Game::receiveBauernumwandlung);
}
//QPushButton *start, QPushButton *quit, QRadioButton *server, QRadioButton *client, QComboBox *whoStarts, QLineEdit *ip, QLineEdit *port, QWidget *parent
Game::~Game()
{
    qDebug()<<"D of Game";
    delete ui;
    ui = nullptr;
}

void Game::start(){
    _chatWindow->setMyName(ui->name->text());
    _myName = ui->name->text();
    emit sendName(ui->name->text());
    ui->whoWon->setDisabled(true);
    ui->whoWon_2->setDisabled(true);
    ui->pointsTop->setDisabled(true);
    if(ui->normalTexture->isChecked()){
        _texturePacket=0;
    }else{
        _texturePacket=1;
    }
    _turnCountBottom=0;
    _turnCountTop=0;
    ui->turnCounterBottom->setText(QString::number(_turnCountBottom));
    ui->turnCounterTop->setText(QString::number(_turnCountTop));
    qDebug()<<"Initialize Setup";
    qDebug()<<_counter<<" 1st time";
    _chessBoard.setup(ui->boardPlaceholder_3, _counter, _yourColor, ui->leftGraveyard, ui->rightGraveyard, _texturePacket);
    ui->groupTop->setText(ui->group->text());
    ui->groupTop->setDisabled(true);
    if(!_counter){
    for(int i=0; i<64; i++){
    connect(_chessBoard._chessTiles[i], &ChessTile::toggled, this, &Game::receiveIdentifier);
    }
    connect(ui->quitGame, &QPushButton::clicked, this, &Game::surrenderOwn);
    }
    if(_yourColor){
        ui->colorPlayer->setText("You are black");
    }else{
        ui->colorPlayer->setText("You are white");
    }
    ui->colorPlayer->setDisabled(true);
    QTimer *timer=new QTimer(this);
    _watch=new Stopwatch(this);
    connect(timer, &QTimer::timeout, this, &Game::updateTime);
    qDebug()<<"Setup vollständig";
    _watch->start();
    timer->start(1000);
    ui->stackedWidget->setCurrentIndex(1);
    QLayoutItem *item;
    while((item=ui->gifSurrenderOwn->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
    while((item=ui->gifLayout->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
    while((item=ui->gifLayout_2->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
    while((item=ui->gifOppSurrendered->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
    //connect()
    //Testing ............
}

void Game::winScreen()
{
    QMovie *movie=new QMovie(":/new/prefix1/spongebobWin.gif", QByteArray(), this);//SELECT_NEW_GIF____
    QLabel *processLabel=new QLabel(this);
    processLabel->setMovie(movie);
    ui->gifLayout->addWidget(processLabel);
    movie->start();

}

void Game::looseScreen()
{
    QMovie *movie=new QMovie(":/new/prefix1/ape123.gif", QByteArray(), this);//______SELECT_NEW_GIF____
    QLabel *processLabel=new QLabel(this);
    processLabel->setMovie(movie);
    ui->gifLayout_2->addWidget(processLabel);
    movie->start();
}

void Game::points(int myPoints, int oppPoints)
{
    if(_yourColor){
        ui->pointsTop->setText(QString::number(myPoints));
        ui->pointsBottom->setText(QString::number(oppPoints));
    }else{
        ui->pointsTop->setText(QString::number(oppPoints));
        ui->pointsBottom->setText(QString::number(myPoints));
    }
}


void Game::receiveIdentifier(int identifier){
    qDebug()<<identifier;
    emit sendIdentifier(identifier);
}

/*void Game::startGame(qint16 port, QString ip, bool isServer, bool begins)
{
    //this->show();
    if(begins){
        _yourColor=0;
    }else{
        _yourColor=1;
    }
    if(port!=0){//Check for Validity to start
    if(!_counter){
    start();
    ++_counter;
    ui->stackedWidget->setCurrentIndex(1);
    }else{
    start();
    ui->stackedWidget->setCurrentIndex(1);
    }
    }
}*/ //Should not be needed because comes from Logic

void Game::surrenderOwn()
{
    ui->stackedWidget->setCurrentIndex(4);
    _chessBoard.destroyGraveyards();
    ui->turnCounterTop->setText(QString::number(0));
    ui->turnCounterBottom->setText(QString::number(0));
    QMovie *movie=new QMovie(":/new/prefix1/ape123.gif", QByteArray(), this);//______SELECT_NEW_GIF____
    QLabel *processLabel=new QLabel(this);
    processLabel->setMovie(movie);
    ui->gifSurrenderOwn->addWidget(processLabel);
    movie->start();
    emit iSurrender();
    _chatWindow->cleanUp();
}

void Game::surrenderOpp()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->turnCounterTop->setText(QString::number(0));
    ui->turnCounterBottom->setText(QString::number(0));
    _chessBoard.destroyGraveyards();
    QMovie *movie=new QMovie(":/new/prefix1/minionsWin.gif",QByteArray(),this);//SELECT_NEW_GIF____
    QLabel *processLabel=new QLabel(this);
    processLabel->setMovie(movie);
    ui->gifOppSurrendered->addWidget(processLabel);
    movie->start();
    _chatWindow->cleanUp();
}

/*void Game::end()
{
    ui->stackedWidget->setCurrentIndex(2);
    endGame();
}*/

void Game::youWin()
{
    _chessBoard.destroyGraveyards();
    ui->turnCounterTop->setText(QString::number(0));
    ui->turnCounterBottom->setText(QString::number(0));
    ui->stackedWidget->setCurrentIndex(2);
    winScreen();
    _won=1;
    _chatWindow->cleanUp();
    if(_yourColor){
        ui->whoWon->setText("Black Won");
    }else{
        ui->whoWon->setText("White Won");
    }
}

void Game::youLose()
{
    _chessBoard.destroyGraveyards();
    ui->turnCounterTop->setText(QString::number(0));
    ui->turnCounterBottom->setText(QString::number(0));
    ui->stackedWidget->setCurrentIndex(3);
    looseScreen();
    _won=0;
    _chatWindow->cleanUp();
    if(_yourColor){
        ui->whoWon_2->setText("White Won");
    }else{
        ui->whoWon_2->setText("Black Won");
    }
}

void Game::receiveNetworkInfo(qint16 port, QString ip, bool isServer, bool begins)
{
    qDebug()<<"Port: "<<port<<" Ip: "<<ip<<" isServer: "<<isServer<<" Begins: "<<begins;
}

void Game::startWin()
{
    qDebug() << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
    ui->stackedWidget->setCurrentIndex(0);
}

void Game::startGui(int yourColor)
{
    qDebug() << "staaaaaaaaaaaaaaart";
    _yourColor=yourColor;
    if(!_counter){
    start();
    ++_counter;
    qDebug()<<"widget ..............";
    ui->stackedWidget->setCurrentIndex(1);
    }else{
    start();
    qDebug()<<"widget ..............";
    ui->stackedWidget->setCurrentIndex(1);
    }
    qDebug() << "currrrrrrrreeeeeeeeeennnnnnnnnnnntttttt :    " << ui->stackedWidget->currentIndex();
}

void Game::error()
{
    qDebug() << "yoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo";
    _errorMessage->show();
    ui->stackedWidget->setCurrentIndex(0);
}

void Game::setGroupnumber(int oppNumber, int oppColor)
{
    if(oppColor){//opp black
        ui->groupTop->setText(QString::number(oppNumber));
        ui->groupBottom->setText(QString::number(6));
    }else{
        ui->groupBottom->setText(QString::number(oppNumber));
        ui->groupTop->setText(QString::number(6));
    }
}

void Game::whoseTurn(int ourTurn)
{
    _ourTurn=ourTurn;
    if(_ourTurn){
        _watch->resume();
    }else{
        _watch->pause();
    }
    _chessBoard.setTurn(_ourTurn);
    if(ourTurn){//wir sind dran
        if(_yourColor){//black
            ++_turnCountTop;
           ui->groupTop->setStyleSheet("color: red;");
           ui->groupBottom->setStyleSheet("color: white");
           ui->turnCounterTop->setStyleSheet("color: red");
           ui->turnCounterTop->setText(QString::number(_turnCountTop));
        }else{
            ++_turnCountBottom;
            ui->groupBottom->setStyleSheet("color: red");
            ui->groupTop->setStyleSheet("color: white;");
            ui->turnCounterBottom->setStyleSheet("color: red");
            ui->turnCounterBottom->setText(QString::number(_turnCountBottom));
        }
    }else{
        if(_yourColor){//black
            ++_turnCountBottom;
           ui->groupBottom->setStyleSheet("color: red;");
           ui->groupTop->setStyleSheet("color: white");
           ui->turnCounterBottom->setText(QString::number(_turnCountBottom));
        }else{
            ++_turnCountTop;
            ui->groupTop->setStyleSheet("color: red");
            ui->groupBottom->setStyleSheet("color: white;");
            ui->turnCounterTop->setText(QString::number(_turnCountTop));
        }
    }
    ui->groupTop->setDisabled(true);
    ui->groupBottom->setDisabled(true);
    ui->turnCounterTop->setStyleSheet("color: white");
    ui->turnCounterBottom->setStyleSheet("color: white");
}

//void Game::receiveBauernumwandlung(int type)
//{
//    //emit emitBauernumwandlung(type);
//}

void Game::updateTime()
{
    qint64 time=_watch->getTime();
    int m=time/1000/60;
    int s=time/1000-m*60;
    ui->timer->setText(QString::number(m)+","+QString::number(s));
}

void Game::rematchClicked(){
    emit rematch();
}
void Game::rematchOpp()
{
    qDebug() << "hhhhhhhhhhhhhhhhheeeeeeeeeeeeeeeeeeeeyyyyyyyyyyyyyyyyyyy";
    ui->stackedWidget->setCurrentIndex(6);
}

void Game::rematchYes()
{
    emit yesrematch();
//    ui->stackedWidget->setCurrentIndex(1);

    //startGui(_yourColor);
}

void Game::rematchNo()
{
    emit noRematch();
    ui->stackedWidget->setCurrentIndex(0);
}

void Game::goBackToLastScene()
{
    _chessBoard.disableAll();
    ui->back->show();
    ui->stackedWidget->setCurrentIndex(1);
    ui->quitGame->hide();
    ui->colorPlayer->hide();
}

void Game::back()
{
    if(_won){
    ui->stackedWidget->setCurrentIndex(2);
    }else{
        ui->stackedWidget->setCurrentIndex(3);
    }
    ui->back->hide();
    ui->quitGame->show();
    ui->colorPlayer->show();
}

void Game::openChat()
{
    _chatWindow->show();
    emit writeName();
}

void Game::toGame()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Game::endIt()
{
    close();
}

void Game::rematchNoOpp()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/*
void Game::setChessBoard(ChessBoard &chesssBoard)
{
    _chessBoard=chesssBoard;
}
*/
void Game::testIdentifiers()
{
    for(int i=0; i<64; i++){
        qDebug()<<_chessBoard._chessTiles[i]->getIdentifier();
    }
}

void Game::lostConnexion(){
    QMessageBox::warning(this,"Connexion lost","Lost connexion with other player");
    ui->stackedWidget->setCurrentIndex(0);
    _chatWindow->cleanUp();
}
