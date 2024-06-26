#ifndef AUDIOREADER_H
#define AUDIOREADER_H

#include <QObject>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QAudioOutput>
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
    cout << audioReader::player->duration() << endl;


    QObject::connect(positionTimer,&QTimer::timeout, this , &audioReader::updateSliderValue);
    QObject::connect(player, &QMediaPlayer::durationChanged, this , &audioReader::updateSliderRange);


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
    void updateSliderRange();





signals:

    void updateSliderValueSignal(int);
    void updateSliderRangeSignal(int);
    void updateMusicNameSignal(QUrl);
};

#endif // AUDIOREADER_H
