/**
 * @file youtubedownloader.h
 * @brief This file handle the download of mp3 files using yt-dlp.
 *
 * This 3rd party package can be found here : [yt-dlp](https://github.com/yt-dlp/yt-dlp)
 */
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


class youtubeDownloader : public QObject
{
    Q_OBJECT
public:
////////////////////    CONSTRUCTOR    ////////////////////
    explicit youtubeDownloader(QObject *parent = nullptr){
//        videoId = "LlN8MPS7KQs";
//        videoTitle = "oneheart x reidenshi - snowfall";

    };

////////////////////    ATTRIBUTS   ////////////////////

    /**
     * @brief QString that holds the command to send to yt-dlp executable. The value is overwritten for every new command.
     */
    QString command;
    /**
     * @brief Path to the music folder (parent).
     *
     * This value is stored as a parmater in params.json.
     * Can be changed at anytime with the GUI.
     */
    QString musicFolder;
    /**
     * @brief Path to the ffmpeg bin folder. FFmpeg is a dependency needed for yt-dlp to work properly.
     *
     * ffmpeg builds can be downloaded from the yt-dlp repository [here](https://github.com/yt-dlp/FFmpeg-Builds?tab=readme-ov-file).
     *
     * This value is stored as a parmater in params.json.
     * Can be changed at anytime with the GUI.
     */
    QString ffmpegPath;

    int result;
    int increment;

    /**
     * @brief Represent the value of the progress bar. This value is used to match visual progression with actual download load.
     *
     */
    int progressBarValue;

    /**
     * @brief QQueue object that stores a list of command. The queue is filled with the youtubeDownloader::downloadAll method, and dequeued every time a download is complete. (1 download at a time)
     *
     */
    QQueue<QString> downloadQueue;


////////////////////    METHODS    ////////////////////
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
