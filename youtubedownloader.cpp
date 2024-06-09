/**
 * @file youtubeDownloader.cpp
 * @brief Implementation of the youtubeDownloader class
 */
#include "youtubeDownloader.h"

void youtubeDownloader::formatCommand(QString videoTitle, QString videoId, QString playlistName){
    command = "yt-dlp.exe -x --audio-format mp3 --audio-quality 192 --write-thumbnail --ffmpeg-location ";
    command += youtubeDownloader::ffmpegPath;
    command += " -P \"";
    command += youtubeDownloader::musicFolder;
    command += "/";
    command += playlistName;
    command += "\" -o \"";
    command += videoTitle;
    command += "\" https://www.youtube.com/watch?v=";
    command += videoId;
    cout << youtubeDownloader::command.toStdString() << endl;
}



void youtubeDownloader::execCommand(QString command){
    QProcess *process = new QProcess(this);
    process->startCommand(command);
    connect(process, &QProcess::finished,this, [=]() {
        process->deleteLater(); // Supprime le processus une fois terminé
        youtubeDownloader::progressBarValue += youtubeDownloader::increment;
        // emit progressBarUpdate(youtubeDownloader::progressBarValue);
        startNextDownload(); // Begin next download
    });

}

void youtubeDownloader::downloadAll(QVector<QString> videoTitleArray,QVector<QString> videoIdArray,QVector<QString> videoThumbnailsUrlArray, QString playlistName){
    cout << playlistName.toStdString() << endl;
    QString newFolderPath = youtubeDownloader::musicFolder + "/" + playlistName;
    cout << "chemin playlist" << newFolderPath.toStdString() << endl;
    QDir dir(newFolderPath);
    if(dir.exists()){
        cout << " Playlist folder already exist" << endl;
    }
    else{
        bool success = dir.mkdir(newFolderPath);
        if(success){
            cout << "creation successful" << endl;
        }
        else{
            cout << "failed to create folder" << endl;
        }
    }

    QStringList fileList = dir.entryList(QStringList() << "*", QDir::Files);
//    for (const QString &fileName : videoTitleArray) {
//        if (fileList.contains(fileName + ".mp3")) {
//            cout << "File " << fileName.toStdString() << " exist" << endl;
//        } else {
//            cout << "File " << fileName.toStdString() << " don't exist" << endl;
//        }
//    }


    youtubeDownloader::increment = 100 / videoTitleArray.size();
    youtubeDownloader::progressBarValue = 0;
    for(int i = 0; i < videoTitleArray.size(); ++i){
        if (fileList.contains(videoTitleArray.at(i) + ".mp3")) {
            cout << "File " << videoTitleArray.at(i).toStdString() << " exist" << endl;
            youtubeDownloader::progressBarValue += youtubeDownloader::increment;
        } else {
            cout << "File " << videoTitleArray.at(i).toStdString() << " don't exist" << endl;
            youtubeDownloader::formatCommand(videoTitleArray.at(i), videoIdArray.at(i), playlistName);
            downloadQueue.enqueue(youtubeDownloader::command);
        }

    }
    if(downloadQueue.isEmpty()){
        cout << "queue empty, leaving ..." << endl;
    }
    else{
        youtubeDownloader::execCommand(downloadQueue.dequeue());
    }



}

void youtubeDownloader::startNextDownload() {
    if (!downloadQueue.isEmpty()) {
        cout << "end of downloading, starting a new one" << endl;
        QString command = downloadQueue.dequeue();
        youtubeDownloader::execCommand(command);
    }
    else{
        // emit progressBarUpdate(100);
        cout << "all download finished" << endl;

    }
}

void youtubeDownloader::updateParams(QString key, QString value){
    if(key == "musicFolder"){
        youtubeDownloader::musicFolder = value;
    }
    else if(key == "ffpmegPath"){
        youtubeDownloader::ffmpegPath = value;
    }
    else{
    }

}
