/**
 * @file youtubedownloader.h
 * @brief Header of the youtubeDownloader class
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

/**
 * @brief The youtubeDownloader class is used to download and extract audio from
 * YouTube videos using the yt-dlp.exe executable.
 */
class youtubeDownloader : public QObject
{
    Q_OBJECT
public:
    explicit youtubeDownloader(QObject *parent = nullptr){
    };

    /**
     * @brief The command string to be executed for downloading and extracting audio.
     */
    QString command;
    /**
     * @brief The command string to be executed for linking audio and thumbnail files.
     */
    QString linkCommand;
    /**
     * @brief The path to the directory where the downloaded audio files will be saved.
     */
    QString musicFolder;
    /**
     * @brief The path to the ffmpeg bin folder.
     */
    QString ffmpegPath;
    /**
     * @brief The value by which the progress bar will be incremented after each
     * successful download.
     */
    int increment;
    /**
     * @brief The current value of the progress bar.
     */
    int progressBarValue;
    /**
     * @brief A queue of command strings to be executed for downloading and extracting
     * audio.
     */
    QQueue<QString> downloadQueue;
    /**
     * @brief A queue of command strings to be executed for linking audio files (mp3) with thumbnails (jpg)
     */
    QQueue<QString> linkCoverQueue;

    QString playlistNameTemp;

    void formatCommand(QString videoTitle, QString videoId, QString playlistName);
    QString formatLinkCommand(QString videoTitle, QString imageTitle, QString outputName);
    void execCommand(QString command);
    void startNextDownload();

    void embedCoverImage();


public slots:
    void downloadAll(QVector<QString>,QVector<QString>,QVector<QString>,QString playlistName);
//    void updateParams(QString,QString);



signals:

    void progressBarValueChanged(int);
};

#endif // YOUTUBEDOWNLOADER_H
