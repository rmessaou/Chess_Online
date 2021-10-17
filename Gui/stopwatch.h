#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <QAbstractItemModel>
#include <QTime>
#include <QtWidgets>

/**
 * @brief The Stopwatch class implements a Stopwatch
 */
class Stopwatch: public QWidget{
    Q_OBJECT
public:
    Stopwatch(QWidget* parent=nullptr);
    /**
     * @brief start start Stopwatch
     */
    void start();
    /**
     * @brief pause pause Stopwatch
     */
    void pause();
    /**
     * @brief resume    resume stopwatch
     */
    void resume();
    /**
     * @brief reset reset Stopwatch
     */
    void reset();
    /**
     * @brief getTime get Time from Stopwatch
     * @return
     */
    qint64 getTime();
    /**
     * @brief isRunning check if Stopwatch runs
     * @return
     */
    bool isRunning();
    /**
     * @brief setRunning
     * @param running
     */
    void setRunning(bool running);
private:
    bool _mRunning;
    qint64 _mTotalTime;
    qint64 _mTempTime;
    QDateTime _mStartTime;
    QTime *_time;
};
#endif // STOPWATCH_H
