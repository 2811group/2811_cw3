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
#include <QScrollArea>
#include <cstring>
#include <QLabel>
#include <QMediaPlayer>
#include "the_player.h"
#include "the_button.h"


class MainWindow : public QGridLayout
{
    Q_OBJECT
private:
    vector<TheButtonInfo> _GetInfoIn(string);  // read in videos and thumbnails to this directory
    void _SetVideoPlayer();  // set the layout of video player
    void _SetVideoShow();  // set the scroll layout to show all videos
    void _SetVideoControl();  // set the video control models

    QWidget *_window;  // the widget of window
    vector<TheButtonInfo> _videos;  // storage all the videos in the folder
    ThePlayer *_player;
    vector<TheButton*> *_buttons;
    QScrollArea *_scrollButton;
    vector<QString> _videoNames;
    QPushButton *_nextVideo;
    QPushButton *_pauseVideo;
    QPushButton *_previousVideo;

public:
    MainWindow(QWidget *parent) : QGridLayout(parent)
    {
        this->_window = parent;
    }
    ~MainWindow() {}

    void AddVideo(int argc, char *argv[]);  // find all the videos in the folder
    void InitWindow();  // set the window widget layout
};

#endif // MAIN_WINDOW_H
