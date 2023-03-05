#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QString>
#include <QSlider>


/*
    Video Player class. It handles additional components like sound volume slider, and other.
*/


// Global enum for video player status
enum Status{

    unloaded,
    loaded,

    playing,
    stopped,
    paused

};

class VideoPlayer : public QWidget{

    Q_OBJECT

public:

    explicit VideoPlayer(QWidget *parent = nullptr, QWidget *destination = nullptr);

    ~VideoPlayer();


public slots:

    void setSrc(QString src);

    void unload();


    void play();

    void stop();

    void pause();

    void playpause();


    void changeProgress(int x);

    void setVolume(int x);

    void setBar(int x);


signals:

    void statusChanged(Status s);


public:

    Status status() {return this->m_status;}

    void setProgress(QSlider *progress);


private:

    Status m_status;


    QSlider *progress;

    QMediaPlayer *mp;

    QVideoWidget *vw;


};

#endif // VIDEOPLAYER_H
