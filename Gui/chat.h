#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QString>
namespace Ui {
class Chat;
}
/**
 * @brief The Chat class: Chat class
 */
class Chat : public QDialog
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    ~Chat();
    /**
     * @brief setName: setter for _name boolean
     */
    void setName(){_name=true;}
    /**
     * @brief setMyName: setter for name of current player
     * @param name
     */
    void setMyName(QString name){_Name=name;}
    /**
     * @brief getOppName: setter for opponent name
     * @return
     */
    QString getOppName(){return _nameOpp;}
    /**
     * @brief cleanUp clears chat window and closes it
     */
    void cleanUp();
public slots:
    /**
     * @brief readMsg: Slot to read message from Textbowser
     */
    void readMsg();
    /**
     * @brief nameOpp: Slot to capture the name of the opponent
     * @param nameOpp
     */
    void nameOpp(QString nameOpp);
    /**
     * @brief chat: slot to write the message captured over network
     * @param msg
     */
    void chat(QString msg);
signals:
    /**
     * @brief writeMsg: sends mssage to network to write it
     * @param msg
     * @param name
     */
    void writeMsg(QString msg, bool name);

private:
    Ui::Chat *ui;
    bool _name;
    QString _Name;
    QString _nameOpp;
};

#endif // CHAT_H
