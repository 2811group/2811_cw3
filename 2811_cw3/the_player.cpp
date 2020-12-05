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
        case QMediaPlayer::State::PausedState:
            _pause_video->setShortcut(QKeySequence(tr("Space")));
            disconnect(_pause_video, SIGNAL(clicked()), this, SLOT(pause()));
            _pause_video->setText("Play");
            connect(_pause_video, SIGNAL(clicked()), this, SLOT(play()));
            break;
        case QMediaPlayer::State::PlayingState:
            _pause_video->setShortcut(QKeySequence(tr("Space")));
            disconnect(_pause_video, SIGNAL(clicked()), this, SLOT(play()));
            _pause_video->setText("Pause");
            connect(_pause_video, SIGNAL(clicked()), this, SLOT(pause()));
            break;
    default:
        break;
    }
}

void ThePlayer::SetPauseButton(QPushButton *button)
{
    _pause_video = button;
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
