#ifndef PROGRESS_TIME_H
#define PROGRESS_TIME_H

#include <QLabel>
#include <QTime>

class ProgressTime : public QLabel
{
    Q_OBJECT
private:
    int _duration;
    int _current;

public:
    ProgressTime() {}
    ~ProgressTime() {}

public slots :
    void SetDurationTime(qint64 duration);  // set the video total time
    void SetCurrentTime(qint64 current);    // set the video current time
};

#endif // PROGRESS_TIME_H
