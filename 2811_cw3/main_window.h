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
#include <QPushButton>
#include <QSlider>
#include <QStyle>
#include "the_player.h"
#include "the_button.h"


class MainWindow : public QGridLayout
{
    Q_OBJECT
private:
    vector<TheButtonInfo> _GetInfoIn(string);  // read in videos and thumbnails to this directory
    void _SetVideoPlayer();         // set the layout of video player
    void _SetVolumeSlider();        // setting the volume slider
    void _SetVideoShow();           // set the scroll layout to show all videos
    void _SetVideoControl();        // set the video control models

    QWidget *_window;               // the widget of window
    vector<TheButtonInfo> _videos;  // storage all the videos in the folder
    ThePlayer *_player;
    vector<TheButton*> *_buttons;   // storage all video buttons
    QScrollArea *_scrollButton;     // create a scroll area
    vector<QString> _videoNames;    // storage all videos' name
    QPushButton *_nextVideo;        // the button of next video
    QPushButton *_previousVideo;    // the button of previous video

    QSlider *_volumeslider;         // volume slider


public:
    MainWindow(QWidget *parent) : QGridLayout(parent)
    {
        this->_window = parent;
    }
    ~MainWindow() {}

    void AddVideo(int argc, char *argv[]);  // find all the videos in the folder
    void InitWindow();  // set the window widget layout

    QPushButton *pauseVideo;       // the button of pause video
    QPushButton *playVideo;       // the button of play video
};


#endif // MAIN_WINDOW_H
