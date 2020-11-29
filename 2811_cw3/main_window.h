#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"


class MainWindow : public QLayout
{
    Q_OBJECT
private:
    vector<TheButtonInfo> _getInfoIn(string);  // read in videos and thumbnails to this directory

    QWidget *_window;  //the widget of window
    vector<TheButtonInfo> _videos;  // storage all the videos in the folder

public:
    MainWindow(QWidget *parent) : QLayout(parent)
    {
        this->_window = parent;
    }
    ~MainWindow();

    void setVideo(int argc, char *argv[]);  // find all the videos in the folder
    void initWindow();  // set the window widget layout
};

#endif // MAIN_WINDOW_H
