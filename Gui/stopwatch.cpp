#include "stopwatch.h"

Stopwatch::Stopwatch(QWidget *parent):QWidget(parent), _mRunning(false), _mTotalTime(0), _mTempTime(0){

}
void Stopwatch::start(){
    _mStartTime=QDateTime::currentDateTime();
    _mRunning=true;
}

void Stopwatch::pause(){
    _mTotalTime+=_mTempTime;
    _mRunning=false;
}

void Stopwatch::resume(){
    _mStartTime=QDateTime::currentDateTime();
    _mRunning=true;
}

bool Stopwatch::isRunning(){
    return _mRunning;
}

void Stopwatch::setRunning(bool running){
    _mRunning=running;
}

qint64 Stopwatch::getTime(){
    if(_mRunning){
    _mTempTime=_mStartTime.msecsTo(QDateTime::currentDateTime());
    qint64 time=_mTotalTime+_mTempTime;
    return time;
    }else{
    qint64 time=_mTotalTime;
    return time;
    }
}
