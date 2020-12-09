#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QSlider>
#include <QMediaPlayer>

class ProgressBar : public QSlider
{
    Q_OBJECT
public:
    ProgressBar() : QSlider(Qt::Horizontal) {};
    ~ProgressBar() {};

public slots:
    void SetDuration(qint64 duration);
    void SetPosition(qint64 position);

};

#endif // PROGRESS_BAR_H
