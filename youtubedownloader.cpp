
#include "youtubedownloader.h"

void youtubedownloader::formatCommand(QString videoTitle, QString videoId, QString playlistName){
//    yt-dlp.exe -x --audio-format mp3 --audio-quality 192 --ffmpeg-location C:/Users/rbarr/OneDrive/Bureau/build-youtube_manager-Desktop_Qt_6_7_0_MSVC2019_64bit-Debug/ffmpeg-master-latest-win64-gpl/bin -o blabla https://www.youtube.com/watch?v=7Q6S19Vvh6s
    command = "yt-dlp.exe -x --audio-format mp3 --audio-quality 192 --write-thumbnail --ffmpeg-location ";
    // command = " -x --audio-format mp3 --audio-quality 192 --write-thumbnail --ffmpeg-location ";
    command += youtubedownloader::ffmpegPath;
    command += " -P ";
    command += youtubedownloader::musicFolder;
    command += "/";
    command += playlistName;
    command += " -o \"";
    command += videoTitle;
    command += "\" https://www.youtube.com/watch?v=";
    command += videoId;
    cout << youtubedownloader::command.toStdString() << endl;
}

void youtubedownloader::execCommand(QString command){
    QProcess *process = new QProcess(this);
    // QString program = "yt-dlp.exe";
    process->startCommand(command);
    connect(process, &QProcess::finished,this, [=]() {
        process->deleteLater(); // Supprime le processus une fois terminé
        youtubedownloader::progressBarValue += youtubedownloader::increment;
        emit progressBarUpdate(youtubedownloader::progressBarValue);
        startNextDownload(); // Commence le prochain téléchargement
    });

}

void youtubedownloader::downloadAll(QVector<QString> videoTitleArray,QVector<QString> videoIdArray,QVector<QString> videoThumbnailsUrlArray, QString playlistName){

//    int i = 0;

    cout << playlistName.toStdString() << endl;
    QString newFolderPath = youtubedownloader::musicFolder + "/" + playlistName;
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


    youtubedownloader::increment = 100 / videoTitleArray.size();
    youtubedownloader::progressBarValue = 0;
    for(int i = 0; i < videoTitleArray.size(); ++i){
        if (fileList.contains(videoTitleArray.at(i) + ".mp3")) {
            cout << "File " << videoTitleArray.at(i).toStdString() << " exist" << endl;
            youtubedownloader::progressBarValue += youtubedownloader::increment;
        } else {
            cout << "File " << videoTitleArray.at(i).toStdString() << " don't exist" << endl;
            youtubedownloader::formatCommand(videoTitleArray.at(i), videoIdArray.at(i), playlistName);
            downloadQueue.enqueue(youtubedownloader::command);
        }

    }
    if(downloadQueue.isEmpty()){
        cout << "queue empty, leaving ..." << endl;
    }
    else{
        youtubedownloader::execCommand(downloadQueue.dequeue());
    }



}

void youtubedownloader::startNextDownload() {
    if (!downloadQueue.isEmpty()) {
        cout << "end of downloading, starting a new one" << endl;
        QString command = downloadQueue.dequeue();
        youtubedownloader::execCommand(command);
    }
    else{
        emit progressBarUpdate(100);
        cout << "all download finished" << endl;

    }
}

void youtubedownloader::updateParams(QString key, QString value){
    if(key == "musicFolder"){
        youtubedownloader::musicFolder = value;
    }
    else if(key == "ffpmegPath"){
        youtubedownloader::ffmpegPath = value;
    }
    else{
    }

}
