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
#include <QPushButton>
#include <QSlider>
#include <QStyle>
#include <QProgressBar>
#include "the_player.h"
#include "the_button.h"


class MainWindow : public QGridLayout
{
    Q_OBJECT
private:
    vector<TheButtonInfo> _GetInfoIn(string);  // read in videos and thumbnails to this directory
    void _SetVideoPlayer();  // set the layout of video player
    void _SetVolumeSlider(); // setting the volume slider
    void _SetVideoShow();  // set the scroll layout to show all videos

    QWidget *_window;  // the widget of window
    vector<TheButtonInfo> _videos;  // storage all the videos in the folder
    ThePlayer *_player;
    vector<TheButton*> *_buttons;
    QScrollArea *_scrollButton;
    vector<QString> _videoNames;
    QSlider *_volumeslider; // volume slider
    QPushButton* one; // button for previous video
    QPushButton* two;  // play button
    QPushButton* pause_button;  // pause button
    QPushButton* three;       // forward button
    QProgressBar *progress;    // progress bar


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
