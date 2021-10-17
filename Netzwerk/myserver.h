#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDataStream>
#include <QTcpSocket>
#include <vector>
#include <QDebug>
#include <QByteArray>
#include <QAbstractSocket>
#include <QString>

class MyServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief MyServer : Constructor of the server
     * @param port : sets the port number
     * @param beginnender : decides who begins
     * @param parent : pointer to the Base Class
     */
    explicit MyServer(quint16 port, quint8 beginnender , QObject *parent = nullptr);
    /**
     * @brief endSignIn : forwards the sign-in information of server to the client
     */
    void endSignIn();

signals:
    /**
     * @brief startInfo : forwards the start information to the server
     * @param we : are we client or server
     * @param beginnender : who begins
     * @param gegnernummer : who are we playing against
     */
    void startInfo(int we, quint8 beginnender, quint8 gegnernummer);
    /**
     * @brief sendVector : contains the data of the move to be sent
     * @param sX : beginning coloumn
     * @param sY : beginning row
     * @param zX : end coloumn
     * @param zY : end row
     * @param status : status of the move
     * @param umwandlung : choice of pawn promotion
     */
    void sendVector(quint8 sX,quint8 sY,quint8 zX,quint8 zY,int status,int umwandlung);
    /**
     * @brief responseToMove : whats the response of the logic to the move
     * @param tmp : status of the response
     */
    void responseToMove(quint8 tmp);
    /**
     * @brief aufgeben : the signal to be sent when the give-up button pushed down
     */
    void aufgeben();
    /**
     * @brief remi : writes the rematch request to the socket
     */
    void remi();
    /**
     * @brief okRematch : positive response of the logic to a request of a rematch
     */
    void okRematch();
    /**
     * @brief noRematch : negative response of the logic to a request of a rematch
     */
    void noRematch();
    /**
     * @brief chat : is emitted when the chat function has been used
     * @param nachricht : written QString message
     */
    void chat(QString nachricht);
    /**
     * @brief sendName : sends the received name to the logic
     * @param sendName : saved name
     */
    void sendName(QString name);
    /**
     * @brief lostConnexion: Signal emitted when connexion lost
     */
    void lostConnexion();
public slots:

    /**
     * @brief recieveName: Slot to capture the opponent name
     * @param name
     */
    void recieveName(QString name);
    /**
     * @brief sessionOpen : opens the session, allows reading and writing functions as well as sending data
     */
    void sessionOpen();
    /**
     * @brief sendData : reads/interprets the data received from the client and sends to logic
     */
    void sendData();
    /**
     * @brief writeData : writes data to stream to send to the client
     * @param movevector : data thats been received from logic
     */
    void writeData(std::vector<quint8> movevector);
    /**
     * @brief rematch : writes the rematch command into the socket
     */
    void rematch();
    /**
     * @brief writeOkRematch : accepts the rematch request and writes it into the socket
     */
    void writeOkRematch();
    /**
     * @brief writeNoRematch : denies the rematch request and writes it into the socket
     */
    void writeNoRematch();
    /**
     * @brief writeMessage: Writes name or message to socket
     * @param msg
     * @param name
     */
    void writeMessage(QString msg, bool name);
    /**
     * @brief disconnect : breaks the connection between client and server
     */
    void disconnect();
    /**
 * @brief writeName: writes name to socket
 */
    void writeName();
    /**
     * @brief connetionError: disconnects server
     */
    void connetionError();

private:
    bool sendname = true;
    /**
     * @brief server : pointer to the server to create the connection
     */
    QTcpServer* server;
    /**
     * @brief stream : saves the data to be sent/recevied in bytes
     */
    QDataStream stream;
    /**
     * @brief socket : a pointer to the socket to allow data transfer
     */
    QTcpSocket* socket;
    /**
     * @brief clients : number of clients
     */
    int clients = 0;
    /**
     * @brief gegnernummer : opponent's group number
     */
    quint8 gegnernummer;
    /**
     * @brief ournumber : our group number
     */
    quint8 ournumber = 0x06;
    /**
     * @brief _port : port number
     */
    quint16 _port;
    /**
     * @brief we : we are the server
     */
    const int we = 0;
    /**
     * @brief _beginnender : the information of who begins
     */
    quint8 _beginnender;
    /**
     * @brief gruppennummer : our group number
     */
    quint8 gruppennummer = 0x06;
    /**
     * @brief socketError object to help display the error
     */
    QAbstractSocket::SocketError socketError;

    QString _name = "";


};

#endif // SERVER_H
