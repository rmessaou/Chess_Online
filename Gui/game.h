#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QGraphicsScene>
#include <iostream>
#include "chessboard.h"
#include "network.h"
#include <QCloseEvent>
#include "stopwatch.h"
#include "errormessage.h"
#include <QStackedWidget>
#include "chat.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE
/**
 * @brief The Game class implements the overarching manager of ui
 */
class Game : public QWidget
{
    Q_OBJECT

public:
    //class ChessBoard;
    /**
     * @brief Game  constructs a game instance
     * @param parent    for QT memory management
     */
    Game(QWidget *parent = nullptr);
    ~Game();
    /**
     * @brief start Starts setup process of ui
     */
    void start();
    /**
     * @brief restart
     */
    void restart();
    /**
     * @brief winScreen
     */
    void winScreen();
    /**
     * @brief looseScreen
     */
    void looseScreen();
    /**
     * @brief getTurn   getter method
     * @return
     */
    bool getTurn(){ return _ourTurn;}
    /**
     * @brief getChat: getter for chat
     * @return
     */
    Chat *getChat(){return _chatWindow;}
public slots:

    /**
     * @brief lostConnexion: Slot to show disconnect error message
     */
    void lostConnexion();
    /**
     * @brief points: Function to calculate the points of each player
     * @param myPoints
     * @param oppPoints
     */
    void points(int myPoints, int oppPoints);
    /**
     * @brief receiveIdentifier loop through identifier sent by ChessTile on click
     * @param identifier
     */
    void receiveIdentifier(int identifier);//receives Identifer after pressed
//    void startGame(qint16 port, QString ip, bool isServer, bool begins=0);//change to just receive bool start=true or false from Server/Logic to start
    /**
     * @brief surrenderOwn  used when player presses surrender button, initializes surrender process
     */
    void surrenderOwn();
    /**
     * @brief surrenderOpp  called by logic when opponent surrenders
     */
    void surrenderOpp();
    /**
     * @brief youWin  opens win screen
     */
    void youWin();
    /**
     * @brief youLose   opens loose screen
     */
    void youLose();
    /**
     * @brief receiveNetworkInfo    Testing purposes
     * @param port
     * @param ip
     * @param isServer
     * @param begins
     */
    void receiveNetworkInfo(qint16 port, QString ip, bool isServer, bool begins=0);
    /**
     * @brief startWin  go to start screen from win screen
     */
    void startWin();
    /**
     * @brief startGui  calls start function, starts gui
     * @param yourColor according to color code
     */
    void startGui(int yourColor);//anstatt startGame, kommt von Logic
    /**
     * @brief error in case of error go to start screen and emit error screen
     */
    void error();
    /**
     * @brief setGroupnumber
     * @param oppNumber
     * @param oppColor
     */
    void setGroupnumber(int oppNumber, int oppColor);
    /**
     * @brief whoseTurn called every turn change
     * @param ourTurn   1-> our turn, 0->enemy turn
     */
    void whoseTurn(int ourTurn);
    /**
     * @brief getNetwork    getter Method
     * @return
     */
    Network* getNetwork(){
        return &_network;
    }
    /**
     * @brief getChessBoard getter Method
     * @return
     */
    ChessBoard* getChessBoard(){
        return &_chessBoard;
    }
    /**
     * @brief receiveBauernumwandlung
     * @param type
     */
    //void receiveBauernumwandlung(int type);//receive from Gui
    /**
     * @brief updateTime    update Time window
     */
    void updateTime();
    /**
     * @brief rematchClicked
     */
    void rematchClicked();
    /**
     * @brief rematchNoOpp: Slot when oppenent doesn't want to rematch
     */
    void rematchNoOpp();
    /**
     * @brief rematchOpp: Slot whenn oppenent clicks of rematch
     */
    void rematchOpp();
    /**
     * @brief rematchYes: Slot when rematch is accepted
     */
    void rematchYes();
    /**
     * @brief rematchNo: Slot when rematch is declined
     */
    void rematchNo();
    /**
     * @brief goBackToLastScene: Slot for back to home button
     */
    void goBackToLastScene();
    /**
     * @brief back: Slot for to return to the last scene when the game ends
     */
    void back();
    /**
     * @brief openChat: Slot for the button to open the chat
     */
    void openChat();
    /**
     * @brief toGame: Slot to open chat
     */
    void toGame();
    /**
     * @brief endIt: Slot to close window
     */
    void endIt();
signals:
    /**
     * @brief sendIdentifier
     * @param identifier
     */
    void sendIdentifier(int identifier);//connected
    /**
     * @brief emitBauernumwandlung
     * @param type
     */
    void emitBauernumwandlung(int type);//send to supervisor what was chosen connected
    /**
     * @brief quitGame
     */
    void quitGame(bool show);
    /**
     * @brief iSurrender
     */
    void iSurrender();
    /**
     * @brief yesrematch: Signal to send an accepted rematch response
     */
    void yesrematch();
    /**
     * @brief rematch: Sends a Signal for a rematch
     */
    void rematch();
    /**
     * @brief noRematch: Signal for declined rematch
     */
    void noRematch();
    /**
     * @brief sendName: sends Name to network
     * @param name
     */
    void sendName(QString name);
    /**
     * @brief writeName: send name over the network
     */
    void writeName();

private:
    Ui::Game *ui;
    ChessBoard _chessBoard;
    int _counter;
    /**
     * @brief testIdentifiers   Testing
     */
    void testIdentifiers();
    Network _network;
    bool _yourColor;
    int _ourTurn;
    Stopwatch *_watch;
    ErrorMessage *_errorMessage;
    int _texturePacket;
    int _turnCountTop;
    int _turnCountBottom;
    int _won;
    Chat *_chatWindow;
    QString _myName = "";
};
#endif // GAME_H
