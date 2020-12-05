#ifndef WIDGET_H
#define WIDGET_H

#include<QVideoWidget>
#include<QDebug>

class Widget : public QVideoWidget
{
    Q_OBJECT
public:
    Widget(QWidget* parent=0) : QVideoWidget(parent) {}
    ~Widget(){}
protected:
    // set the doubleclick event and keyboard event
    void mouseDoubleClickEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
};


#endif
