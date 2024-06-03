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

    /**
     * @brief integer that represents the increment value for 1 download in the progressBar. Updated everytime the youtubeDownloader::downloadAll method is called.
     *
     */
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
    /**
     * @fn formatCommand
     * @brief format the command to be executed with the yt-dlp.exe. The command is stored in the youtubeDownloader::command QString
     *
     * @param videoTitle    Title of the video to be added to the command (used for output file name).
     * @param videoId   Id of the video used for the request, as it appears in the URL of the video (after the watch?v= ).
     * @param playlistName  Name of the playlist selected, used to rename the output mp3 files.
     *
    */
    void formatCommand(QString videoTitle, QString videoId, QString playlistName);
    /**
     * @fn execCommand
     * @brief Starts a Qprocess and execute yt-dlp.exe with the command as a parameter. This method also handles the refresh of the progressBar value.
     *
     * Emits the signal \ref progressBarUpdate to update the frontend.
     *
     * At the end of the QProcess, youtubeDownloader::startNextDownload is called.
     *
     * @param command   QString that represent the command to be executed.
     *
    */
    void execCommand(QString command);
    /**
     * @fn startNextDownload
     * @brief load the next command from the
     *
     * Emits the signal \ref progressBarUpdate to update the frontend.
     *
     * At the end of the QProcess, youtubeDownloader::startNextDownload is called.
     *
    */
    void startNextDownload();


public slots:
    void downloadAll(QVector<QString>,QVector<QString>,QVector<QString>,QString playlistName);
    void updateParams(QString,QString);



signals:

    void progressBarUpdate(int);
};

#endif // YOUTUBEDOWNLOADER_H
