#include "chesstile.h"
#include <iostream>
//ChessTile::ChessTile()
//{

//}
/**
 * @brief ChessTile::ChessTile Konstruktor eines ChessTiles
 * @param text  Text der auf dem Button displayed werden soll
 * @param color Farbe des Buttons
 * @param identifier    Identifier des Buttons von 0 links unten nach 63 rechts oben
 * @param parent    übergabe des Zeigers auf ChessBoard, Speicherverwaltung durch QT
 * @param _2identfier   für Bauernumwandlung um Typ festzulegen
 */
ChessTile::ChessTile(QString text, bool color, int identifier, QWidget *parent,
                     int _2identfier, bool isHighlighted, int iconSize, bool disabled):
                     QPushButton(text, parent), _identifier(identifier), _color(color),
                     _2_identifier(_2identfier), _isHighlighted(isHighlighted), _disabled(disabled)
{
    if(color==0){//0-->hell, 1-->dunkel
    this->setStyleSheet("QPushButton{background-color: rgb(224, 224, 224)}");
    }else{
        this->setStyleSheet("QPushButton{background-color: rgb(70, 70,70)}");
    }
    _checks=false;
    _color=color;
    //this->setMaximumSize(QSize(100,100));
    this->setMaximumWidth(63);
    this->setMaximumHeight(63);
    this->setMinimumWidth(62);
    this->setMinimumHeight(62);
    /*this->setMaximumWidth(40);
    this->setMaximumHeight(40);*/
    connect(this, &ChessTile::clicked, this, &ChessTile::checkEnabled);
                    //connect(this, &ChessTile::clicked, this, &ChessTile::clickedReaction);
                    //connect(this, &ChessTile::clicked, this, &ChessTile::clickedTransformation);
    connect(this, &ChessTile::checkedClick, this, &ChessTile::clickedReaction);
    connect(this, &ChessTile::checkedClick, this, &ChessTile::clickedTransformation);
    connect(this, &ChessTile::hovered, this, &ChessTile::colorWhenHover);
    connect(this, &ChessTile::left, this, &ChessTile::uncolorWhenleave);
    this->setIcon(QIcon());
    this->setIconSize(QSize(iconSize,iconSize));
    std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
}

void ChessTile::clickedReaction()
{
      emit toggled(_identifier);
}

void ChessTile::clickedTransformation()
{
    std::cout<<_identifier<<"  "<<_2_identifier<<std::endl;
    emit transformationToggle(_identifier, !_color, _2_identifier);
}


void ChessTile::enterEvent(QEvent *e)
{
    std::cout<<"+++++++++++++Hovered++++++++++++"<<std::endl;
    emit hovered();
    QWidget::enterEvent(e);
}

void ChessTile::colorWhenHover()
{
    if(_color&&!_isHighlighted&&!_disabled){
    this->setStyleSheet("QPushButton{background-color: rgb(128, 128, 128)}");
    }else if(!_isHighlighted&&!_disabled){
    this->setStyleSheet("QPushButton{background-color: rgb(255, 255, 255)}");
    }else if(!_disabled){
    this->setStyleSheet("QPushButton{background-color: rgb(255, 204, 153)}");
    }
}

void ChessTile::uncolorWhenleave()
{
    if(_color&&!_isHighlighted&&!_disabled){//black
        this->setStyleSheet("QPushButton{background-color: rgb(70, 70,70)}");
    }else if(!_isHighlighted&&!_disabled){//white
        this->setStyleSheet("QPushButton{background-color: rgb(224, 224, 224)}");
    }else if(!_disabled&&!_checks){
    this->setStyleSheet("QPushButton{background-color: rgb(255, 153, 51)}");
    }else if(!_disabled){
        this->setStyleSheet("QPushButton{background-color: rgb(153, 0, 0)}");
    }
}

void ChessTile::leaveEvent(QEvent *e)
{
    emit left();
    QWidget::leaveEvent(e);
}

void ChessTile::checkEnabled()
{
    if(!_disabled){
        emit checkedClick();
    }
}

void ChessTile::disable(){
    //QIcon prev=this->icon();
    //                                          this->setDisabled(true);
    _disabled=true;
    /*if(_color){
        this->setStyleSheet("QPushButton{background-color: rgb(70, 70,70)}");
    }else{
        this->setStyleSheet("QPushButton{background-color: rgb(224, 224, 224)}");
    }
    this->setStyleSheet("background-image: url(prev);");*/
}

void ChessTile::enable(){
    //                                              this->setEnabled(true);
    _disabled=false;
}

void ChessTile::highlight()
{
    this->setStyleSheet("QPushButton{background-color: rgb(255, 153, 51)}");
    _isHighlighted=true;
}

void ChessTile::defaultColor(bool color)
{
    if(color){
    this->setStyleSheet("QPushButton{background-color: rgb(70, 70,70)}");
    }else{
        this->setStyleSheet("QPushButton{background-color: rgb(224, 224, 224)}");
    }
    _isHighlighted=false;
}

void ChessTile::highlightCheck()
{
    this->setStyleSheet("QPushButton{background-color: rgb(153, 0, 0)}");
    _isHighlighted=true;
}

void ChessTile::highlightKingCheck()
{
    this->setStyleSheet("QPushButton{background-color: rgb(0, 255, 0)}");
    _isHighlighted=true;
}

void ChessTile::highlightTurn()
{
    if(_color){
    this->setStyleSheet("QPushButton{border:3px solid rgb(0, 255, 255); background-color: rgb(70, 70,70)}");
    }else{
    this->setStyleSheet("QPushButton{border:3px solid rgb(0, 255, 255); background-color: rgb(224, 224, 224)}");
    }
    _isHighlighted=true;
}

