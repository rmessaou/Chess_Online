#include "supervisor.h"

Supervisor::Supervisor()
{
    game = new Game();//normaly should receive this pointer for memory management, but somehow does not work
    chess = new Chess();

    //############################ GAME START CONNECTS ############################
    //###########################################################################

    connect(game->getNetwork(), &Network::clientSetup, this, &Supervisor::initClient);
    connect(game->getNetwork(), &Network::serverSetup, this, &Supervisor::initServer);

    //############################ GUI/LOGIC MOVES ########################################
    //#############################################################################

    connect(chess, &Chess::whoseTurn, game, &Game::whoseTurn);
    connect(chess, &Chess::sendOppData, game, &Game::setGroupnumber);
    connect(chess, &Chess::startGui, game, &Game::startGui);
    connect(chess, &Chess::bauerUmwandlungOpp, game->getChessBoard(), &ChessBoard::receivePawnTransformationOpp); //bauer umwandlung of opponent----LOOK FOR CORRECT PARAM ORDER
    connect(chess, &Chess::myBauerUmwandlung, game->getChessBoard(), &ChessBoard::pawnTransformation); //my bauer umwandlung in GUI ?// Did not know about 2. int
    connect(chess, &Chess::enPassant, game->getChessBoard(), &ChessBoard::enPassant); //enPassant Slot in GUI ?
    connect(chess, &Chess::modifyGui, game->getChessBoard(), &ChessBoard::move); //move is function .. chessboard private .. move erwartet 2 params
    connect(chess, &Chess::whereToMove, game->getChessBoard(), &ChessBoard::showPossible); //show possible slot ?
    connect(chess, &Chess::hilightCheck, game->getChessBoard(), &ChessBoard::checkHighlight); // Um check zu connecten
    connect(chess, &Chess::weWin, game, &Game::youWin);
    connect(chess, &Chess::weLose, game, &Game::youLose);
    connect(chess, &Chess::pointsCounter, game, &Game::points);
    connect(chess, &Chess::errorState, game, &Game::error); //without params .. muss gui implementieren#


    //############################# GAME END CONNECTS ###############################
    //##############################################################################

    connect(game->getChessBoard(), &ChessBoard::bauernumwandlung, chess, &Chess::myBauerChange); //bauerumwandlung signal where?
    connect(game, &Game::sendIdentifier, chess, &Chess::moveFromGUI); //where slot to send click
    connect(game, &Game::iSurrender, chess, &Chess::mySurrender); // when GUI clickt auf button
    connect(game, &Game::yesrematch, chess, &Chess::rematch); //damit my GUI verandert wird nach dem ich yes clicke


    game->show();
}

void Supervisor::initClient(quint16 port, QString ip ){
    qDebug() << "I m here 2";
    client = new MyClient(ip,port);


    //############################### CLIENT/LOGIC CONNECTS ############################
    //##################################################################################

    connect(client, &MyClient::startInfo, chess, &Chess::setColors);
    connect(client, &MyClient::sendVector, chess, &Chess::moveFromNetwork);
    connect(client, &MyClient::responseToMove, chess, &Chess::responseFromNetwork);

    //###################################################################################

    connect(chess, &Chess::ourMove, client, &MyClient::writeData);
    connect(chess, &Chess::ourResponse, client, &MyClient::writeData);
    connect(chess, &Chess::surrender, client, &MyClient::writeData);
    connect(chess, &Chess::errorState,client,&MyClient::disconnect);

    //############################### GUI/CLIENT CONNECTS ############################
    //##################################################################################


    connect(game, &Game::quitGame, client, &MyClient::disconnect);
    connect(game, &Game::rematch, client, &MyClient::rematch);
    connect(game, &Game::noRematch, client, &MyClient::writeNoRematch); //schreibe an socket
    connect(game, &Game::yesrematch, client, &MyClient::writeOkRematch); //schreibe an socket
    connect(game->getChat(), &Chat::writeMsg, client ,&MyClient::writeMessage);
    connect(game, &Game::sendName, client, &MyClient::recieveName);
    connect(game, &Game::writeName, client, &MyClient::writeName);
//    connect(game->getNetwork(), &Network::sendName,client, &MyClient::recieveName);

    //##################################################################################

    connect(client, &MyClient::sendName, game->getChat(), &Chat::nameOpp);
    connect(client, &MyClient::aufgeben, game, &Game::surrenderOpp); // we win surrender by gui uber netz
    connect(client, &MyClient::chat, game->getChat(), &Chat::chat);
    connect(client, &MyClient::remi, game, &Game::rematchOpp);
    connect(client, &MyClient::noRematch, game, &Game::rematchNoOpp); // damit my GUI back zu HOME geht
    connect(client, &MyClient::okRematch, chess, &Chess::rematch); // damit my GUI verandert wird nachdem andere yes clicke
    connect(client, &MyClient::lostConnexion, game, &Game::lostConnexion);


}

void Supervisor::initServer(quint16 port, int begins){
    qDebug() << "I m here 1";

    server = new MyServer(port,static_cast<quint8>(begins));

    //############################### SERVER/LOGIC CONNECTS ############################
    //##################################################################################

    connect(server, &MyServer::sendVector, chess, &Chess::moveFromNetwork);
    connect(server, &MyServer::responseToMove, chess, &Chess::responseFromNetwork);
    connect(server, &MyServer::startInfo, chess, &Chess::setColors);

    //##################################################################################

    connect(chess, &Chess::ourMove, server, &MyServer::writeData);
    connect(chess, &Chess::surrender, server, &MyServer::writeData);
    connect(chess, &Chess::ourResponse, server, &MyServer::writeData);
    connect(chess, &Chess::errorState,server,&MyServer::disconnect);


    //############################### GUI/SERVER CONNECTS ############################
    //##################################################################################

    connect(game, &Game::quitGame, server, &MyServer::disconnect);
    connect(game, &Game::rematch, server, &MyServer::rematch);
    connect(game, &Game::yesrematch, server, &MyServer::writeOkRematch); //schreibe an socket
    connect(game, &Game::noRematch, server, &MyServer::writeNoRematch); //schreibe an socket
    connect(game->getChat(), &Chat::writeMsg, server,&MyServer::writeMessage);
    connect(game, &Game::sendName, server, &MyServer::recieveName);
    connect(game, &Game::writeName, server, &MyServer::writeName);
//    connect(game->getNetwork(), &Network::sendName,server, &MyServer::recieveName);

    //##################################################################################

    connect(server, &MyServer::remi, game, &Game::rematchOpp);
    connect(server, &MyServer::okRematch, chess, &Chess::rematch); // damit my GUI verandert wird nachdem andere yes clicke
    connect(server, &MyServer::aufgeben, game, &Game::surrenderOpp); // uber netz
    connect(server, &MyServer::noRematch, game, &Game::rematchNoOpp); // damit my GUI back zu HOME geht
    connect(server, &MyServer::sendName, game->getChat(), &Chat::nameOpp);
    connect(server, &MyServer::chat, game->getChat(), &Chat::chat);
    connect(server, &MyServer::lostConnexion, game, &Game::lostConnexion);

}

Supervisor::~Supervisor()
{
delete game;
delete chess;
if(server != nullptr){
    delete server;
    server = nullptr;
}
if(client != nullptr){
    delete client;
    client = nullptr;
}
game = nullptr;
chess = nullptr;
}
