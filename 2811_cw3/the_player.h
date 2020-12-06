//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

using namespace std;

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    vector<TheButtonInfo>* _infos;
    vector<TheButton*>* _buttons;
    int _currentVideo;
    QPushButton *_pause_video;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)),
                 this, SLOT (_playStateChanged(QMediaPlayer::State)) );
    }

    // all buttons have been setup, store pointers here
    void setContent(vector<TheButton*>* b, vector<TheButtonInfo>* i);

    // connect pause in ThePlayer and MainWindow together
    void SetPauseButton(QPushButton *button);


private slots:

    void _playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void JumpNext ();
    void JumpPrevious ();

    // set the video positon use slider
    void SetPosition(int position);
};

#endif //CW2_THE_PLAYER_H
