#include "main_window.h"

// read in videos and thumbnails to this directory
vector<TheButtonInfo> MainWindow::_GetInfoIn(string loc)
{
    vector<TheButtonInfo> out =  vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            // get the videos name
            QStringList list1 = f.split("/");
            QString allName = list1[list1.length()-1];
            QStringList list2 = allName.split(".");
            QString name = list2[0];
            // storage the videos name to vector
            _videoNames.push_back(allName);

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video "
                                    "because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping "
                            "video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}

void MainWindow::AddVideo(int argc, char **argv)
{
    if (argc == 2)
    {
        _videos = _GetInfoIn( string(argv[1]) );
    }
    else
    {
        _videos = _GetInfoIn("../../videos");  // If user does not input anything, program will find videos here
    }

    if (_videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to "
                            "\"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke"
                                         "_leeds_ac_uk/EcGntcL-K3JOiaZF4T_"
                                         "uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }
}

void MainWindow::InitWindow()
{
    this->_SetVideoPlayer();
    this->_SetVideoControl();
    this->_SetVolumeSlider();
    this->_SetProgressBar();
    this->_SetVideoShow();

    // space betweem the row
    setSpacing(5);
}

void MainWindow::_SetVideoPlayer()
{
    // the widget that will show the video
    Widget *videoWidget = new Widget();


    // the QMediaPlayer which controls the playback
    _player = new ThePlayer;

    _player->setVideoOutput(videoWidget);

    this->addWidget(videoWidget, 0, 0, 2, 6);
}

void MainWindow::_SetVolumeSlider()
{
    // set volumeslider
    this->_volumeslider=new QSlider(Qt::Horizontal);
    _volumeslider->setRange(0, 100);
    _volumeslider->setFixedWidth(125);
    _volumeslider->setValue(20);        //init volume

    connect(_volumeslider, SIGNAL(valueChanged(int)),
            _player, SLOT(setVolume(int)));
    connect(_player, SIGNAL(volumeChanged(int)),
            _volumeslider, SLOT(setValue(int)));

    this->addWidget(_volumeslider, 2, 5, 1, 1);
}

void MainWindow::_SetProgressBar(){
    QWidget *progress = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    // set the progress bar
    _progress = new ProgressBar();
    _progressDurationLabel = new ProgressTime();
    _progressCurrentLabel = new ProgressTime();

    connect(_player, SIGNAL(durationChanged(qint64)),
            _progress, SLOT(SetDuration(qint64)));
    connect(_player, SIGNAL(positionChanged(qint64)),
            _progress, SLOT(SetPosition(qint64)));
    connect(_progress, SIGNAL(valueChanged(int)),
            _player, SLOT(SetPosition(int)));
    connect(_player, SIGNAL(durationChanged(qint64)),
            _progressDurationLabel, SLOT(SetDurationTime(qint64)));
    connect(_player, SIGNAL(positionChanged(qint64)),
            _progressCurrentLabel, SLOT(SetCurrentTime(qint64)));

//    _progressCurrentLabel->SetCurrentLabel();
//    _progressDurationLabel->SetDurationLabel();

    layout->addWidget(_progressCurrentLabel);
    layout->addWidget(_progress);
    layout->addWidget(_progressDurationLabel);
    progress->setLayout(layout);

    this->addWidget(progress,2,4,1,1);
}

void MainWindow::_SetVideoShow()
{
    //set scorll area for video buttons
    this->_scrollButton = new QScrollArea();
    // a row of buttons
    QWidget *buttonWidget = new QWidget(_scrollButton);
    // a list of the buttons
    _buttons = new vector<TheButton*>();
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout(_scrollButton);
    buttonWidget->setLayout(layout);

    // set the size of the widget in scroll area
    buttonWidget->setFixedWidth(250*_videos.size());
    buttonWidget->setFixedHeight(200);
    _scrollButton->setAlignment(Qt::AlignCenter);

    // create the four buttons
    for ( size_t i = 0; i < _videos.size(); i++ ) {
        // set layout for each button and video name
        QVBoxLayout *vLayout = new QVBoxLayout();
        // set widget for each button and video name
        QWidget *allButton = new QWidget(buttonWidget);
        //set the button for the each video button
        TheButton *button = new TheButton(allButton);
        // set the label for video name
        QLabel *text = new QLabel(_videoNames.at(i).toStdString().data());
        text->setAlignment(Qt::AlignCenter);

        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )),
                        _player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        _buttons->push_back(button);
        button->init(&_videos.at(i));

        vLayout->addWidget(button);
        vLayout->addWidget(text);

        allButton->setLayout(vLayout);
        layout->addWidget(allButton);
    }
    // tell the player what buttons and videos are available
    _player->setContent(_buttons, &_videos);

    // add widget in to scroll area and set height
    _scrollButton->setWidget(buttonWidget);
    _scrollButton->setFixedHeight(235);
    this->addWidget(_scrollButton, 3, 0, 1, 6);
}

void MainWindow::_SetVideoControl()
{
    // set the previous video push button
    _previousVideo = new QPushButton("⬅");
    _previousVideo->setShortcut(QKeySequence(Qt::Key_Left));
    connect(_previousVideo, SIGNAL(clicked()), _player, SLOT(JumpPrevious()));

    // set the play/pause video push button
    pauseVideo = new QPushButton();
    _player->SetPauseButton(pauseVideo);
    QMediaPlayer::connect(_player, SIGNAL(stateChanged(QMediaPlayer::State)),
                          _player, SLOT(_playStateChanged(QMediaPlayer::State)));
    QPushButton::connect(pauseVideo, SIGNAL(clicked()), _player, SLOT(pause()));


    // set the next video push button
    _nextVideo = new QPushButton("⮕");
    _nextVideo->setShortcut(QKeySequence(Qt::Key_Right));
    connect(_nextVideo, SIGNAL(clicked()), _player, SLOT(JumpNext()));


    QHBoxLayout *controlLayout = new QHBoxLayout();
    controlLayout->addWidget(_previousVideo);
    controlLayout->addWidget(pauseVideo);
    controlLayout->addWidget(_nextVideo);

    QWidget *controlArea = new QWidget();
    controlArea->setLayout(controlLayout);

    this->addWidget(controlArea, 2, 0, 1, 4);
}





























































