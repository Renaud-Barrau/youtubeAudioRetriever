#ifndef AUDIOREADER_H
#define AUDIOREADER_H

#include <QObject>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QAudioOutput>
// #include <QMediaPlaylist>
#include <QUrl>
#include <QTimer>



#include <iostream>

using namespace std;

class audioReader : public QObject
{
    Q_OBJECT
public:
////////////////////    CONSTRUCTEUR    ////////////////////
    explicit audioReader(QObject *parent = nullptr){



        player = new QMediaPlayer(this);
        positionTimer = new QTimer(this);

        audioReader::player->setAudioOutput(&audioOutput);
        audioReader::player->setSource(QUrl::fromLocalFile("C:/Users/rbarr/Desktop/musique_test/Musique/Jack Junior - My Addiction.mp3"));
        audioReader::player->pause();


        QObject::connect(positionTimer,&QTimer::timeout, this , &audioReader::updateSliderValue);


    };

////////////////////    ATTRIBUTS   ////////////////////

    QTimer *positionTimer;
    QMediaPlayer *player;
    QAudioOutput audioOutput;


////////////////////    METHODES    ////////////////////

public slots:

    void playYouTubeVideo(const QString &videoUrl);
    void playLocalAudio(const QString &filePath);
    void togglePlayback();
    void changeAudio(QString path);
    void setPosition(int position);
    void updateSliderValue();





signals:
};

#endif // AUDIOREADER_H
