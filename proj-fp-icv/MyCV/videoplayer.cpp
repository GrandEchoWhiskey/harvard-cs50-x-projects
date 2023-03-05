#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent, QWidget *destination) : QWidget{parent}{

    // Malloc
    this->mp = new QMediaPlayer(parent);
    this->vw = new QVideoWidget();

    // Set wideo output to widget
    this->mp->setVideoOutput(this->vw);
    this->m_status = Status::unloaded;

    // Put the widget over the destination widget, and copy size
    this->vw->setGeometry(destination->geometry());
    this->vw->setParent(parent);

    // Show widget
    this->vw->show();

    // Connect progress slider
    connect(mp, &QMediaPlayer::positionChanged, this, &VideoPlayer::setBar);

}

VideoPlayer::~VideoPlayer(){

    // Free memory
    delete this->mp;
    delete this->vw;

}

void VideoPlayer::changeProgress(int x){

    // Change position of progress slider
    this->mp->setPosition(x);

}

void VideoPlayer::setProgress(QSlider *progress){

    // Copy pointer to progress slider
    this->progress = progress;

}

void VideoPlayer::setVolume(int x){

    // Change video volume
    this->mp->setVolume(x);

}

void VideoPlayer::setBar(int x){

    // Change progress value and max value
    if(this->progress != nullptr){
        this->progress->setMaximum(this->mp->duration());
        this->progress->setValue(x);
    }

}

void VideoPlayer::setSrc(QString src){

    // Set media source
    this->mp->setMedia(QUrl::fromLocalFile(src));
    this->m_status = Status::loaded;

    // Emit singnal that status changed
    emit this->statusChanged(this->m_status);

}

void VideoPlayer::unload(){

    this->mp->setMedia(nullptr);

    // Change media status
    this->m_status = Status::unloaded;

    // Emit singnal that status changed
    emit this->statusChanged(this->m_status);

}

void VideoPlayer::play(){

    // Return if unloaded
    if(this->m_status == Status::unloaded) return;

    // Set max progress on slider
    if(this->progress != nullptr)
        this->progress->setMaximum(this->mp->duration());

    // Play
    this->mp->play();
    this->m_status = Status::playing;

    // Emit singnal that status changed
    emit this->statusChanged(this->m_status);

}

void VideoPlayer::stop(){

    // Return if unloaded
    if(this->m_status == Status::unloaded) return;

    // Stop
    this->mp->stop();
    this->m_status = Status::stopped;

    // Emit singnal that status changed
    emit this->statusChanged(this->m_status);

}

void VideoPlayer::pause(){

    // Return if unloaded
    if(this->m_status == Status::unloaded) return;

    // Pause
    this->mp->pause();
    this->m_status = Status::paused;

    // Emit singnal that status changed
    emit this->statusChanged(this->m_status);

}


void VideoPlayer::playpause(){

    // Swap play/pause
    if(this->m_status == Status::playing)
        this->pause();

    else
        this->play();

}
