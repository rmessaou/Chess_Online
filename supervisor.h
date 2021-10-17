#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include "Netzwerk/myserver.h"
#include "Netzwerk/myclient.h"
#include "Logik/chess.h"
#include "Gui/game.h"

class Supervisor : public QWidget
{
    Q_OBJECT

public:
    Supervisor();
    ~Supervisor();

private:
    Game* game = nullptr;
    MyServer* server = nullptr;
    MyClient* client = nullptr;
    Chess* chess = nullptr;

public slots:
    /**
     * @brief initClient: initialises a client instance
     * @param port
     * @param ip
     */
    void initClient(quint16 port, QString ip );

    /**
     * @brief initServer: initialises a server instance
     * @param port
     * @param begins
     */
    void initServer(quint16 port, int begins);
};

#endif // SUPERVISOR_H

