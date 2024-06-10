/**
 * @file youtubeDownloader.cpp
 * @brief Implementation of the youtubeDownloader class
 */
#include "youtubeDownloader.h"


/**
 * @brief Formats the command to extract and download audio from a YouTube video using the yt-dlp.exe executable.
 *
 * This method takes three input parameters: videoTitle, videoId, and playlistName.
 * It constructs a command string using these input parameters and stores it in the command member variable.
 * The command string is constructed as follows:
*
* - "yt-dlp.exe" : the name of the executable to run
* - "-x" : extract audio from the video
* - "--audio-format mp3" : set the audio format to mp3
* - "--audio-quality 192" : set the audio quality to 192 kbps
* - "--write-thumbnail" : write the video thumbnail to the output file
* - "--ffmpeg-location" : the path to the ffmpeg executable, which is used by yt-dlp.exe to extract and encode audio
* - "-P" : the path to the output directory, which is specified as a combination of the musicFolder and playlistName member variables
* - "-o" : the output file name, which is specified as the videoTitle input parameter
* - "https://www.youtube.com/watch?v=" : the URL of the YouTube video, which is specified as a combination of the "https://www.youtube.com/watch?v=" string and the videoId input parameter
*
* The command string is then printed to the console using cout.
*
* @param videoTitle The title of the YouTube video.
* @param videoId The ID of the YouTube video.
* @param playlistName The name of the playlist of the wanted video.
*/
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


/**
 * @brief Executes the command to extract and download audio from a YouTube video using the yt-dlp.exe executable in the background.
 *
 * This method takes one input parameter: command, which is the command string constructed by the formatCommand() method.
 * It creates a new QProcess object and starts the command using the startCommand() method.
 * It then connects the finished() signal of the QProcess object to a lambda function that deletes the QProcess object and updates the progress bar.
 * The progress bar is updated by incrementing the progressBarValue member variable.
 * The startNextDownload() method is then called to start the next download in the queue, if any.
 *
* @param command The command string to be executed.
*/
void youtubeDownloader::execCommand(QString command){
    QProcess *process = new QProcess(this);
    process->startCommand(command);
    connect(process, &QProcess::finished,this, [=]() {
        process->deleteLater();
        youtubeDownloader::progressBarValue += youtubeDownloader::increment;
        // emit progressBarUpdate(youtubeDownloader::progressBarValue);
        startNextDownload();
    });
}



/**
 * @brief Downloads all the videos in a playlist and extracts their audio.
 *
 * This method takes four input parameters:
- videoTitleArray: A QVector of QString containing the titles of the videos in the playlist.
- videoIdArray: A QVector of QString containing the IDs of the videos in the playlist.
- videoThumbnailsUrlArray: A QVector of QString containing the URLs of the thumbnails of the videos in the playlist.
- playlistName: A QString containing the name of the playlist.
 *
 * It first checks if the playlist folder already exists, and if not, it creates a new folder with the given playlist name.
 * Then, it gets a list of all the files in the playlist folder.
 * It calculates the progress bar increment value based on the number of videos in the playlist.
 * It then loops through the videoTitleArray and checks if the corresponding video file already exists in the playlist folder.
 * If the file exists, it increments the progress bar value.
 * If the file does not exist, it calls the formatCommand() method to create the command string for extracting and downloading the audio of the video.
 * It then adds the command string to the downloadQueue queue.
 * Finally, if the downloadQueue is not empty, it calls the execCommand() method to start the first command in the queue.
 *
 * @param videoTitleArray: A QVector of QString containing the titles of the videos in the playlist.
 * @param videoIdArray: A QVector of QString containing the IDs of the videos in the playlist.
 * @param videoThumbnailsUrlArray: A QVector of QString containing the URLs of the thumbnails of the videos in the playlist.
 * @param playlistName: A QString containing the name of the playlist.
 */
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


/**
 * @brief Starts the next download in the queue, if any.
 *
 * This method checks if the downloadQueue queue is not empty.
 * If it is not empty, it dequeues the next command string from the queue and calls the execCommand() method to start the command.
 * If the queue is empty, it prints a message to the console indicating that all downloads have been completed.
 *
 * @param None
 * @return None
 */
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



//void youtubeDownloader::updateParams(QString key, QString value){
//    if(key == "musicFolder"){
//        youtubeDownloader::musicFolder = value;
//    }
//    else if(key == "ffpmegPath"){
//        youtubeDownloader::ffmpegPath = value;
//    }
//    else{
//    }

//}
