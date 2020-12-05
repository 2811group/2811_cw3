/*widget.cpp*/
#include"widget.h"
#include<QMouseEvent>


void Widget::mouseDoubleClickEvent(QMouseEvent* event)
{
    // use the left double click to make it full screen
    // use the right double click to make it normal
    if(event->button()==Qt::LeftButton)
    {
        setWindowFlags (Qt::Window);
        showFullScreen();
    }
    else if(event->button()==Qt::RightButton)
    {
        setWindowFlags (Qt::SubWindow);
        showNormal ();
    }
}

void Widget::keyPressEvent(QKeyEvent *keyset)
{
    // use the "f" to make it full screen
    // use the "esc" to make it normal
    if(keyset->key()==Qt::Key_Escape)
    {
         setWindowFlags (Qt::SubWindow);
         showNormal ();
    }
    else if (keyset->key()==Qt::Key_F)
    {
        setWindowFlags (Qt::Window);
        showFullScreen();
    }
}
