 #ifndef MYCLIENT_H
#define MYCLIENT_H


#include <QObject>
#include <QTcpServer>
#include <QDataStream>
#include <QTcpSocket>
#include <vector>
#include <QDebug>
#include <QByteArray>

class MyClient : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief MyClient : Constructor of MyClient
     * @param _host  : name of host
     * @param _port : port number
     * @param parent : pointer to the Base Class
     */
    explicit MyClient(QString _host, quint16 _port, QObject* parent = nullptr);

public slots:

    void recieveName(QString name);
    /**
     * @brief connectToServer : provides the connection to the host
     */
    void connectToServer();
    /**
     * @brief readData : reads the data that has been sent by Logic
     */
    void readData();
    /**
     * @brief writeData : sends data through a vector over QDataStream
     * @param movevector : contains all to be sent data
     */
    void writeData(std::vector<quint8> movevector);
    /**
     * @brief signIn sends over the group number of the client to the server
     */
    void signIn();
    /**
     * @brief rematch : signals the rematch request
     */
    void rematch();
    /**
     * @brief writeOkRematch : signals that the rematch request has been accepted
     */
    void writeOkRematch();
    /**
     * @brief writeNoRematch : signals that the rematch request has been rejected
     */
    void writeNoRematch();
    /**
     * @brief writeMessage: writes name or message in socket
     * @param msg
     * @param name
     */
    void writeMessage(QString msg, bool name);
    /**
     * @brief disconnect : breaks the connection between client and server
     */
    void disconnect();
    /**
     * @brief writeName to socket
     */
    void writeName();
    /**
     * @brief connetionError: disconnects from server
     */
    void connetionError();

private:
    bool sendname = true;
    /**
     * @brief stream : stream in/out for binary data
     */
    QDataStream stream;
    /**
     * @brief socket : a pointer to the socket that provides the data transfer
     */
    QTcpSocket *socket;
    /**
     * @brief gruppennummer : our group number
     */
    quint8 gruppennummer = 0x06;
    /**
     * @brief host : name of the host to be connected
     */
    QString host;
    /**
     * @brief port : the port number to be connected
     */
    quint16 port ;
    /**
     * @brief wir : whether we are client or server
     */
    const int wir = 1;

    QString _name = "";

signals:
    /**
     * @brief sendVector : contains the data of the move to be sent
     * @param vector : beginning coloumn
     * @param vector1 : beginning row
     * @param vector2 : end coloumn
     * @param vector3 : end row
     * @param a : status of the move
     * @param b : choice of pawn promotion
     */
    void sendVector(quint8 vector,quint8 vector1,quint8 vector2, quint8 vector3, int a, int b);
    /**
     * @brief responseToMove : signal of the response to move
     * @param variable : status of the response
     */
    void responseToMove(quint8 variable);
    /**
     * @brief startInfo : containts the starting information of the opponent/our
     * @param wir : are we server or client
     * @param vector : who is beginning
     * @param gegnernummer : the group number of the opponent
     */
    void startInfo(quint8 wir,quint8 vector, quint8 gegnernummer);
    /**
     * @brief aufgeben gets emitted when the give up button is pushed down
     */
    void aufgeben();
    /**
     * @brief remi :
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
     * @brief chat
     * @param nachricht
     */
    void chat(QString nachricht);
    /**
     * @brief name
     * @param name
     */
    void sendName(QString name);
    /**
     * @brief lostConnexion: disconnects from client
     */
    void lostConnexion();
};


#endif
