#include "supervisor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Supervisor w;


    return a.exec();
}
