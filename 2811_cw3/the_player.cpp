//
// Created by twak on 11/11/2019.
//
#include "the_player.h"
#include "main_window.h"


using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    _buttons = b;
    _infos = i;
    _currentVideo = 0;
    jumpTo(_buttons -> at(_currentVideo) -> info);
}

void ThePlayer::_playStateChanged (QMediaPlayer::State ms) {
    // set the play/pause button
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::SetPauseButton(QPushButton *button)
{
    _pause_video = button;
    _pause_video->setText("Pause");
}

void ThePlayer::SetPlayButton(QPushButton *button)
{
    _play_video = button;
    _play_video->setText("Play");
}

void ThePlayer::SetPosition(int position)
{
    QMediaPlayer::setPosition(qint64(position));
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
}

void ThePlayer::JumpNext () {
    _currentVideo = (_currentVideo + 1) % _buttons->size();
    setMedia( * _infos->at(_currentVideo).url);
    play();
}

void ThePlayer::JumpPrevious () {
    _currentVideo = (_currentVideo - 1) % _buttons->size();
    setMedia( * _infos->at(_currentVideo).url);
    play();
}
