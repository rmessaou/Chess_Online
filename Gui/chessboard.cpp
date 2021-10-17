#include "chessboard.h"
#include <QGridLayout>
#include <iostream>
#include <QDebug>
//#include <QMediaPlayer>//added-----------
//#include <QSound>
#include <QTimer>
/**
 * @brief ChessBoard::ChessBoard
 * @param parent pointer auf übergeordnetes Widget Game für automatisches Zerstören durch QT
 * Aufruf zum Start der Anwendung, ist Attribut der übergeordneten Game classe
 */
ChessBoard::ChessBoard(QWidget* parent): QWidget(parent)
{
    //_chessBoard=std::make_shared<ChessBoard>(*this);
//    _chessPieces=new ChessPieces();
    qDebug()<<"C of ChessBoard#######################";
}
/**
 * @brief ChessBoard::setup Erzeugt/Ordnet das Spielfeld auf Anfangszustand
 * @param grid  pointer auf QGridLayout(boardPlaceholder_3), übergeben von Game (ui->boardPlaceholder_3)
 * @param counter   beim 1. Setup aufruf 0, wenn counter==0 werden CHessTiles neu gebaut, danch immer 1 (für erneuten Spielstart), wenn counter==1 werden nur die Figuren umgesetzt
 */
void ChessBoard::setup(QGridLayout *grid, int counter, bool yourColor, QGridLayout *leftGraveyard, QGridLayout *rightGraveyard, int texturePacket)
{
    _texturePacket=texturePacket;
    _yourColor=yourColor;
    _rightGraveyard=rightGraveyard;
    _leftGraveyard=leftGraveyard;
    qDebug()<<"------SETUP------";
    qDebug()<<"------SETUP--STEP--2------";
    if(!counter){
    qDebug()<<counter<<" 1st time";
    placeChessTiles(grid, this);
    }
    qDebug()<<counter<<" 1st time";
    //ChessPieces *chessPieces=new ChessPieces(); Eins höher verlegt
    for(int i=8; i<16; i++){
    //_chessTiles[i]->setIcon(*(chessPieces->_chessPieces[11])); Sah alles so aus
     if(_texturePacket==1){
     _chessTiles[i]->setIcon(_chessPieces._chessPieces[11]);
     }else{
     _chessTiles[i]->setIcon(_chessPieces._chessPieces[23]);
     }
    }
    qDebug()<<"Placed Pawns white";
    for(int i=48; i<56; i++){
    //_chessTiles[i]->setIcon(*(chessPieces->_chessPieces[5]));
    if(_texturePacket==1){
    _chessTiles[i]->setIcon(_chessPieces._chessPieces[5]);
    }else{
    _chessTiles[i]->setIcon(_chessPieces._chessPieces[17]);
    }
    }
    qDebug()<<"Placed Pawns black";
    if(_texturePacket==1){
     //schwarz
    _chessTiles[56]->setIcon(_chessPieces._chessPieces[4]);
    _chessTiles[57]->setIcon(_chessPieces._chessPieces[3]);
    _chessTiles[58]->setIcon(_chessPieces._chessPieces[2]);
    _chessTiles[59]->setIcon(_chessPieces._chessPieces[1]);
    _chessTiles[60]->setIcon(_chessPieces._chessPieces[0]);
    _chessTiles[61]->setIcon(_chessPieces._chessPieces[2]);
    _chessTiles[62]->setIcon(_chessPieces._chessPieces[3]);
    _chessTiles[63]->setIcon(_chessPieces._chessPieces[4]);
    //weiß
    _chessTiles[0]->setIcon(_chessPieces._chessPieces[10]);
    _chessTiles[1]->setIcon(_chessPieces._chessPieces[9]);
    _chessTiles[2]->setIcon(_chessPieces._chessPieces[8]);
    _chessTiles[3]->setIcon(_chessPieces._chessPieces[7]);
    _chessTiles[4]->setIcon(_chessPieces._chessPieces[6]);
    _chessTiles[5]->setIcon(_chessPieces._chessPieces[8]);
    _chessTiles[6]->setIcon(_chessPieces._chessPieces[9]);
    _chessTiles[7]->setIcon(_chessPieces._chessPieces[10]);
    }else{
        //schwarz
       _chessTiles[56]->setIcon(_chessPieces._chessPieces[16]);
       _chessTiles[57]->setIcon(_chessPieces._chessPieces[15]);
       _chessTiles[58]->setIcon(_chessPieces._chessPieces[14]);
       _chessTiles[59]->setIcon(_chessPieces._chessPieces[13]);
       _chessTiles[60]->setIcon(_chessPieces._chessPieces[12]);
       _chessTiles[61]->setIcon(_chessPieces._chessPieces[14]);
       _chessTiles[62]->setIcon(_chessPieces._chessPieces[15]);
       _chessTiles[63]->setIcon(_chessPieces._chessPieces[16]);
       //weiß
       _chessTiles[0]->setIcon(_chessPieces._chessPieces[22]);
       _chessTiles[1]->setIcon(_chessPieces._chessPieces[21]);
       _chessTiles[2]->setIcon(_chessPieces._chessPieces[20]);
       _chessTiles[3]->setIcon(_chessPieces._chessPieces[19]);
       _chessTiles[4]->setIcon(_chessPieces._chessPieces[18]);
       _chessTiles[5]->setIcon(_chessPieces._chessPieces[20]);
       _chessTiles[6]->setIcon(_chessPieces._chessPieces[21]);
       _chessTiles[7]->setIcon(_chessPieces._chessPieces[22]);
    }
    disableAll();
    if(counter){
        for(int i=16; i<48; i++){
            _chessTiles[i]->setIcon(QIcon());
        }
    }
    qDebug()<<"SETUP!!";
}
/**
 * @brief ChessBoard::placeChessTiles   Erzeugt und plaziert ChessTiles, ruft dazu placeChessTileColumn auf
 * @param grid  pointer auf QGridLayout(boardPlaceholder_3), übergeben von Game (ui->boardPlaceholder_3)
 * @param parent    übergibt Zeiger auf chessBoard instanz, zur Speicherverwaltung durch QT
 */
void ChessBoard::placeChessTiles(QGridLayout* grid, QWidget* parent){
    /*QGridLayout* grid=new QGridLayout(game);
    grid->setVerticalSpacing(0);
    grid->setHorizontalSpacing(0);*/
    /*ui->verticalLayout_2->boardPlaceholder->setHorizontalSpacing(0);
    ui->verticalLayout_2->boardPlaceholder->setVerticalSpacing(0);*/
    grid->setHorizontalSpacing(8);
    grid->setVerticalSpacing(8);
    for(int i=0; i<8; i++){
        /*ChessTile *chessTile=new ChessTile(QString(""), 1);
        _chessTiles.append(chessTile);*/

        placeChessTileRow(i, grid, parent/*, chessTile*/);
    }
    //ui->gridLayout->addLayout(grid,0,0);
    /*grid->setVerticalSpacing(0);
    grid->setHorizontalSpacing(0);*/
}
/**
 * @brief ChessBoard::placeChessTileColumn Aufgerufen durch placeChessTiles, Helper-function um eine Reihe ChessTiles zu erzeugen
 * @param row   Zeilennummer, 0 indiziert, von oben nach unten
 * @param grid  pointer auf QGridLayout(boardPlaceholder_3), übergeben von Game (ui->boardPlaceholder_3)
 * @param parent    übergibt Zeiger auf chessBoard instanz, zur Speicherverwaltung durch QT
 */
void ChessBoard::placeChessTileRow(int row, QGridLayout *grid, QWidget *parent/*, ChessTile* chessTile*/){
    static int rythm=1;
    for(int i=0; i<8; i++){
        if(rythm%2==0){
        ChessTile *chessTile=new ChessTile(QString(""), 0, 8*row+i, parent, 0, false, 55); //WICHTIG FALLS SHARED PTR NICHT WOLLEN!!!!!!!!!!!
        //std::shared_ptr<ChessTile> chessTile=std::make_shared<ChessTile>(QString(""), 0, 8*row+i);
        _chessTiles.append(chessTile);
        //connect(chessTile, &ChessTile::toggle, game, &Game::receiveIdentifier);
        //ui->boardPlaceholder->addWidget(chessTile, 8-row, i);
        //ui->boardPlaceholder_3->addWidget(_chessTiles[8*row+i].get(), 8-row, i);
        grid->addWidget(chessTile, 8-row, i);
        }else{
        ChessTile *chessTile=new ChessTile(QString(""), 1, 8*row+i, parent, 0, false, 55); //WICHTIG FALLS SHARED PTR NICHT WOLLEN!!!!!!!!!!!!
        //std::shared_ptr<ChessTile> chessTile=std::make_shared<ChessTile>(QString(""), 1, 8*row+i);
        _chessTiles.append(chessTile);
        //ui->boardPlaceholder->addWidget(chessTile, 8-row, i);
        //ui->boardPlaceholder_3->addWidget(_chessTiles[8*row+i].get(), 8-row, i);
        grid->addWidget(chessTile, 8-row, i);
        }
    ++rythm;
    qDebug()<<_chessTiles[8*row+i]->getIdentifier();
    }
    ++rythm;
}
/**
 * @brief ChessBoard::move  Bewegt Figur von start zu end, Aufgerufen durch Logic, bei eigenem sowie bei gegnerzug
 * @param start Anfangsposition
 * @param end   Endposition
 * @param strike    Noch nicht genutzt, evtl. um Figur off-Field zu stellen
 */
void ChessBoard::move(int start, int end, bool strike)//0-->no strike, 1-->strike //TODO
{
 showPossibleOff();
 if(strike){//Strike
     //QMediaPlayer *strikeSound=new QMediaPlayer();
     //strikeSound->setMedia(QUrl("qrc:/new/prefix1/salamisound-6589668-schlag-auf-metall-eisen.mp3"));
     //strikeSound->play();
     //QSound strikeSound=QSound(":/new/prefix1/strikeSound");
     //strike.play();
     QIcon chessPiece=_chessTiles[start]->icon();
     QIcon striked=_chessTiles[end]->icon();
     _chessTiles[start]->setIcon(QIcon());
     _chessTiles[end]->setIcon(chessPiece);
    ChessTile* chessTile=new ChessTile(QString(""), 0, 0, this, 0, false, 55);
    chessTile->disable();
    //QIcon empty=QIcon();
    int lrow;
    int lcolumn;
    lrow=static_cast<int>(_leftGraveyard->count()/2)+1;
    lcolumn=_leftGraveyard->count()%2+1;
    int rrow;
    int rcolumn;
    rrow=static_cast<int>(_rightGraveyard->count()/2)+1;
    rcolumn=_rightGraveyard->count()%2+1;
    if(_yourColor&&_ourTurn){
        _leftGraveyard->addWidget(chessTile, lrow, lcolumn);
        chessTile->setIcon(striked);
    }else if(!_yourColor&&_ourTurn){
        _rightGraveyard->addWidget(chessTile, rrow, rcolumn);
        chessTile->setIcon(striked);
    }else if(_yourColor&&!_ourTurn){
        _rightGraveyard->addWidget(chessTile, rrow, rcolumn);
        chessTile->setIcon(striked);
    }else if(!_yourColor&&!_ourTurn){
        _leftGraveyard->addWidget(chessTile, lrow, lcolumn);
        chessTile->setIcon(striked);
    }
     qDebug()<<"Strike";
 }else{//no Strike
    QIcon chessPiece=_chessTiles[start]->icon();
    _chessTiles[start]->setIcon(QIcon());
    _chessTiles[end]->setIcon(chessPiece);
    qDebug()<<"No Strike";
 }
 qDebug() << "from GUI start " << start << " end " << end ;

}
/**
 * @brief ChessBoard::showPossible Zeigt mögliche Züge an wenn eigene Figur gedrückt wurde (highlighting in rot), aufgerufen durch Logic,
 * wenn man am Zug ist (possible dann leer), sowie nachdem 1 clicked() signal empfangen wurde
 * @param possible  std::vector<int> mit den möglichen Feldern (0 indiziert)
 * @param yourTiles std::vector<int> mit Positionen der eigenen Figuren (0 indiziert)
 */
void ChessBoard::showPossible(std::vector<int> possible, std::vector<int> yourTiles)
{   showPossibleOff();
    if(possible.size()!=0){
    enable(possible);
    enable(yourTiles);
    for(int possible: possible){
        _chessTiles[possible]->highlight();
    }
    }else{
        enable(yourTiles);
        for(int mine: yourTiles){
            _chessTiles[mine]->highlightTurn();
        }
        QTimer::singleShot(500, this, [=](){for(int mine: yourTiles){
                _chessTiles[mine]->defaultColor(_chessTiles[mine]->getColor());
            }});
    }
}
/**
 * @brief ChessBoard::showPossibleOff aufgerufen von move, disabled alle ChessTiles und setzt sie wider auf die Standardfarbe
 */
void ChessBoard::showPossibleOff()//TODO
{
    disableAll();
    defaultColorAll();
}
/**
 * @brief ChessBoard::defaultColorAll aufgerufen durch showPossibleOff, setzt alle ChessTiles auf die Standardfarbe
 */
void ChessBoard::defaultColorAll()//TODO can be Improved as color already memorized by ChessTiles
{
    int offset=1;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
        _chessTiles[i*8+j]->defaultColor(offset%2);
        ++offset;
     }
    ++offset;
    }
}
/**
 * @brief ChessBoard::disableAll    deaktiviert alle Felder, aufgerufen durch showPossibleOff
 */
void ChessBoard::disableAll()
{
    for(int i=0; i<64; i++){
        _chessTiles[i]->disable();
    }
}
/**
 * @brief ChessBoard::enableAll aktiviert alle Felder
 */
void ChessBoard::enableAll()
{
    for(int i=0; i<64; i++){
        _chessTiles[i]->enable();
    }
}
/**
 * @brief ChessBoard::enable aufgerufen von showPossible, Hilfsfunktion um nur die eigenen Felder zu enablen zum Start des eigenen Zuges (wenn possible leer)
 * @param yourTiles enthält die Positionen an denen eigene Figuren stehen
 */
void ChessBoard::enable(std::vector<int> yourTiles)
{
    if(yourTiles.size()!=0){
    for(int toEnable:yourTiles){
        _chessTiles[toEnable]->enable();
    }
    }
}
/**
 * @brief ChessBoard::moveTest TEST von Move
 */
void ChessBoard::moveTest()
{
    for(int i=0; i<32; i++){
        move(i, i+8);
    }
    for(int i=63; i>31; i--){
        move(i, i-8);
    }
}
/**
 * @brief ChessBoard::rochade implementiert Rochade, aufgerufen durch Logic
 * @param pos1  Position des Königs
 * @param pos2  Position des Turms
 * @param type  Art der Rochade (0==kurz, 1==lang)
 */
void ChessBoard::rochade(int pos1, int pos2, bool type)//pos1 King, pos2 Tower
{
    if(type){//lange rochade
    QIcon newKing=_chessTiles[pos1]->icon();//get King Icon
    _chessTiles[pos1-2]->setIcon(newKing);
    QIcon newTower=_chessTiles[pos2]->icon();//get Tower Icon
    _chessTiles[pos2+3]->setIcon(newTower);
    }else{//kurze rochade
    QIcon newKing=_chessTiles[pos1]->icon();//get King Icon
    _chessTiles[pos1+2]->setIcon(newKing);
    QIcon newTower=_chessTiles[pos2]->icon();//get Tower Icon
    _chessTiles[pos2-2]->setIcon(newTower);
}
    _chessTiles[pos1]->setIcon(QIcon());
    _chessTiles[pos2]->setIcon(QIcon());
    disableAll();
}
/**
 * @brief ChessBoard::pawnTransformation    Implementiert Bauernentwicklung, aufruf durch Logic wenn eigene Bauernentwicklung stattfindet
 * @param pos   Position des Bauern
 */
void ChessBoard::pawnTransformation(int pos)//1-->bishop, 2-->knight, 3-->tower, 4-->queen
{
    //_choiceWidget->show();
    qDebug()<<"++++++##"<<pos<<"##++++++";
    QVector<ChessTile*> transformationVector;
    for(int i=0; i<4; i++){
    ChessTile *chessTile=new ChessTile("", !_yourColor, pos, nullptr, i+1);
    transformationVector.append(chessTile);
    _choiceLayout->addWidget(chessTile);
    connect(chessTile, &ChessTile::transformationToggle, this, &ChessBoard::receivePawnTransformation);
    }
    if(_texturePacket==1){
    if(!_yourColor){
    transformationVector[0]->setIcon(_chessPieces._chessPieces[8]);
    transformationVector[1]->setIcon(_chessPieces._chessPieces[9]);
    transformationVector[2]->setIcon(_chessPieces._chessPieces[10]);
    transformationVector[3]->setIcon(_chessPieces._chessPieces[7]);
    }else{
        transformationVector[0]->setIcon(_chessPieces._chessPieces[2]);
        transformationVector[1]->setIcon(_chessPieces._chessPieces[3]);
        transformationVector[2]->setIcon(_chessPieces._chessPieces[4]);
        transformationVector[3]->setIcon(_chessPieces._chessPieces[1]);
    }
    }else{
        if(!_yourColor){
        transformationVector[0]->setIcon(_chessPieces._chessPieces[20]);
        transformationVector[1]->setIcon(_chessPieces._chessPieces[21]);
        transformationVector[2]->setIcon(_chessPieces._chessPieces[22]);
        transformationVector[3]->setIcon(_chessPieces._chessPieces[19]);
        }else{
            transformationVector[0]->setIcon(_chessPieces._chessPieces[14]);
            transformationVector[1]->setIcon(_chessPieces._chessPieces[15]);
            transformationVector[2]->setIcon(_chessPieces._chessPieces[16]);
            transformationVector[3]->setIcon(_chessPieces._chessPieces[13]);
        }
    }
}
/**
 * @brief ChessBoard::enPassant
 * @param pos   Position der Figur die enPassant geschlagen wird
 */
void ChessBoard::enPassant(int pos)
{
    int lrow;
    int lcolumn;
    lrow=static_cast<int>(_leftGraveyard->count()/2)+1;
    lcolumn=_leftGraveyard->count()%2+1;
    int rrow;
    int rcolumn;
    rrow=static_cast<int>(_rightGraveyard->count()/2)+1;
    rcolumn=_rightGraveyard->count()%2+1;
    QIcon pawn=_chessTiles[pos]->icon();
    _chessTiles[pos]->setIcon(QIcon());
    ChessTile* chessTile=new ChessTile(QString(""), 0, 0, this, 0, false, 55);
    chessTile->disable();
    if(_yourColor&&_ourTurn){
        _leftGraveyard->addWidget(chessTile, lrow, lcolumn);
        chessTile->setIcon(pawn);
    }else if(!_yourColor&&_ourTurn){
        _rightGraveyard->addWidget(chessTile, rrow, rcolumn);
        chessTile->setIcon(pawn);
    }else if(_yourColor&&!_ourTurn){
        _rightGraveyard->addWidget(chessTile, rrow, rcolumn);
        chessTile->setIcon(pawn);
    }else if(!_yourColor&&!_ourTurn){
        _leftGraveyard->addWidget(chessTile, lrow, lcolumn);
        chessTile->setIcon(pawn);
    }
    //std::cout<<"######EnPassant#####"<<std::endl;
}
/**
 * @brief ChessBoard::setChoice Setzt das Attribut _choiceLayout welches auf ein QHBoxLayout zeigt, übergabe durch Game in der Initialisierungsliste
 * @param choiceLayout
 */
void ChessBoard::setChoice(QHBoxLayout *choiceLayout/*, QWidget *choiceWidget*/)
{
    _choiceLayout=choiceLayout;
    //_choiceWidget=choiceWidget;
}

void ChessBoard::destroyGraveyards()
{
    QLayoutItem *item;
    while((item=_leftGraveyard->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
    while((item=_rightGraveyard->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
}
/**
 * @brief ChessBoard::receivePawnTransformation Slot erhält komplette Bauerntransformation und führt sie aus
 * @param pos   Stelle an der Figur steht
 * @param type  Art der Figur die gesetzt werden soll (1==bishop, 2==knight, 3==tower, 4==queen)
 * @param color Farbe der Figur (0==Weiß, 1==Schwarz)
 */
void ChessBoard::receivePawnTransformation(int pos, int color, int type)//also for enemy with if case and offset
{
    qDebug()<<"-------"<<pos<<"----------"<<type<<"---------"<<color<<"--------";
    if(!color){//weiß
    if(type==4){//special case dame, because unterschied in Ordnung
    //_chessTiles[pos]->setIcon(_chessPieces->_chessPieces[type+3]);
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+3]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+15]);
        }
    }else{
    //_chessTiles[pos]->setIcon(_chessPieces->_chessPieces[type+7]);
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+7]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+19]);
        }
    }
    }else{
    if(type==4){//special case dame, because unterschied in Ordnung
    //_chessTiles[pos]->setIcon(_chessPieces->_chessPieces[type-3]);
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type-3]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+9]);
        }
    }else{
    //_chessTiles[pos]->setIcon(_chessPieces->_chessPieces[type+1]);
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+1]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+13]);
        }
    }
    }
    QLayoutItem *item;
    while((item=_choiceLayout->takeAt(0))!=nullptr){
        delete item->widget();
        delete item;
    }
    qDebug()<< "GUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << type;
    emit bauernumwandlung(type);
}

void ChessBoard::receivePawnTransformationOpp(int pos, int color, int type)//also for enemy with if case and offset
{
    qDebug()<<"-------"<<pos<<"----------"<<type<<"---------"<<color<<"--------";
    if(!color){//weiß
    if(type==4){//special case dame, because unterschied in Ordnung
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+3]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+15]);
        }
    }else{
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+7]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+19]);
        }
    }
    }else{
    if(type==4){//special case dame, because unterschied in Ordnung
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type-3]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+9]);
        }
    }else{
        if(_texturePacket==1){
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+1]);
        }else{
    _chessTiles[pos]->setIcon(_chessPieces._chessPieces[type+13]);
        }
    }
    }
}

void ChessBoard::checkHighlight(std::vector<int> possible, int posKing)
{
    for(int mark:possible){
        _chessTiles[mark]->highlightCheck();
    }
    _chessTiles[posKing]->highlightKingCheck();
}
