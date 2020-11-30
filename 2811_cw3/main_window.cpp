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
            _videoNames.push_back(name);

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
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
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
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
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
    this->_SetVideoShow();
}

void MainWindow::_SetVideoPlayer()
{
    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget();

    // the QMediaPlayer which controls the playback
    _player = new ThePlayer;
    _player->setVideoOutput(videoWidget);
    this->addWidget(videoWidget, 0, 0, 2, 1);
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
    buttonWidget->setFixedHeight(150);
    _scrollButton->setAlignment(Qt::AlignCenter);

    // create the four buttons
    for ( size_t i = 0; i < _videos.size(); i++ ) {
        TheButton *button = new TheButton(_scrollButton);

        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), _player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        _buttons->push_back(button);
        layout->addWidget(button);
        button->init(&_videos.at(i));
        printf("%s\n",_videoNames.at(i).toStdString().data());
    }
    // tell the player what buttons and videos are available
    _player->setContent(_buttons, &_videos);

    // add widget in to scroll area and set height
    _scrollButton->setWidget(buttonWidget);
    _scrollButton->setFixedHeight(180);
    this->addWidget(_scrollButton, 2, 0, 1, 1);
}
