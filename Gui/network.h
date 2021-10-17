#ifndef NETWORK_H
#define NETWORK_H
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QLineEdit>
#include <iostream>
//#include <QRandomGenerator>
#include <cstdlib>
/**
 * @brief The Network class implements the Network Gui elements on the start screen
 */
class Network: public QObject
{ Q_OBJECT
public:
    Network()=default;
    /**
     * @brief Network constructor of Network
     * @param parent    for QT memory management
     */
    Network(QWidget* parent=nullptr);
    /**
     * @brief setUp set all attributes of Network, each parameter is pointer to according Gui element
     * @param start
     * @param quit
     * @param server
     * @param client
     * @param youBegin
     * @param opponenBegins
     * @param ip
     * @param port
     * @param group
     * @param randomBeginner
     * @param parent
     */
    void setUp(QPushButton *start, QPushButton *quit, QRadioButton *server, QRadioButton *client, QRadioButton *youBegin, QRadioButton *opponenBegins, QLineEdit *ip, QLineEdit *port, QLineEdit *group, QRadioButton *randomBeginner, QRadioButton *animalTexture, QLineEdit* name);
    ~Network(){std::cout<<"-------efseff++++fsfsdf----"<<std::endl;}
    QPushButton *_start;
    /**
     * @brief serverMode    enable Server mode (disable and enable according ui elements)
     */
    void serverMode();
    /**
     * @brief clientMode    enable client mode (disable and enable according ui elements)
     */
    void clientMode();
    /**
     * @brief getIsServer   getter Method
     */
    void getIsServer();
    /**
     * @brief getWhoStarts  getter Method
     */
    void getWhoStarts();
public slots:
    /**
     * @brief start activated when start is pressed
     */
    void start();
signals:
    /**
     * @brief clientSetup emitted to setup as Server
     * @param port
     * @param ip
     * @param isServer
     * @param begins
     */
    void clientSetup(qint16 port, QString ip, bool isServer, bool begins,QString name);//connected
    /**
     * @brief serverSetup   emitted to setup Client
     * @param port
     * @param begins
     * @param ip
     * @param isServer
     */
    void serverSetup(qint16 port, int begins, QString ip , bool isServer,QString name);//connected
   // void sendName(QString name, bool isname);
private:
    QWidget *_quit;
    QRadioButton *_server;
    QRadioButton *_client;
    QRadioButton *_youBegin;
    QRadioButton *_opponentBegins;
    QLineEdit *_ip;
    QLineEdit *_port;
    qint16 port;
    QString ip;
    QLineEdit* _group;
    bool isServer;
    bool begins;
    QRadioButton *_randomBeginner;
    QRadioButton *_animalTexture;
    QLineEdit* _name;
};

#endif // NETWORK_H


//qint16 port, QString ip, bool isServer, bool starts=0
