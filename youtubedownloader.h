
#ifndef YOUTUBEDOWNLOADER_H
#define YOUTUBEDOWNLOADER_H


#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QProcess>
#include <QQueue>
#include <QDir>



#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;


class youtubedownloader : public QObject
{
    Q_OBJECT
public:
////////////////////    CONSTRUCTEUR    ////////////////////
    explicit youtubedownloader(QObject *parent = nullptr){
//        videoId = "LlN8MPS7KQs";
//        videoTitle = "oneheart x reidenshi - snowfall";

    };

////////////////////    ATTRIBUTS   ////////////////////
    QString command;
    QString musicFolder;
    QString ffmpegPath;// = "C:/Users/rbarr/OneDrive/Bureau/build-youtube_manager-Desktop_Qt_6_7_0_MSVC2019_64bit-Debug/ffmpeg-master-latest-win64-gpl/bin";
//    string videoId;
//    string videoTitle;

    int result;
    int increment;
    int progressBarValue;
    // QNetworkReply* reply;
    QQueue<QString> downloadQueue;


////////////////////    METHODES    ////////////////////
    void formatCommand(QString videoTitle, QString videoId, QString playlistName);
    void execCommand(QString command);
    void startNextDownload();


public slots:
    void downloadAll(QVector<QString>,QVector<QString>,QVector<QString>,QString playlistName);
    void updateParams(QString,QString);



signals:
    void progressBarUpdate(int);
};

#endif // YOUTUBEDOWNLOADER_H
