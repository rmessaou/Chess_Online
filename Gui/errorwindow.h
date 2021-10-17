#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H
#include <QWidget>

class ErrorWindow: public QWidget
{
public:
    ErrorWindow();
    void showError();
private:
};

#endif // ERRORWINDOW_H
