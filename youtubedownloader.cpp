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
    command = "yt-dlp.exe -x --audio-format mp3 --audio-quality 192 --write-thumbnail --convert-thumbnails jpg --ffmpeg-location ";
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
        emit progressBarValueChanged(youtubeDownloader::progressBarValue);
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
    emit progressBarValueChanged(0);
    youtubeDownloader::playlistNameTemp=playlistName;
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
    cout << "taille : " << videoTitleArray.size() << endl;
    youtubeDownloader::increment = 90 / videoTitleArray.size();
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
        youtubeDownloader::execCommand(downloadQueue.dequeue());
    }
    else{
        // emit progressBarUpdate(100);
        cout << "all download finished" << endl;
        youtubeDownloader::embedCoverImage();

    }
}


QString youtubeDownloader::formatLinkCommand(QString videoTitle, QString imageTitle, QString outputName){
    linkCommand = youtubeDownloader::ffmpegPath.replace("/","\\");
    linkCommand += "\\ffmpeg.exe";
    linkCommand += " -i ";
    linkCommand+= "\"";
    linkCommand += videoTitle;
    linkCommand+= "\"";
    linkCommand += " -i ";
    linkCommand+= "\"";
    linkCommand += imageTitle;
    linkCommand+= "\"";
    linkCommand += " -map 0 -map 1 -c copy -id3v2_version 3 -metadata:s:v title=\"Album cover\" -metadata:s:v comment=\"Cover (front)\" ";
    linkCommand+= "\"";
    linkCommand += outputName;
    linkCommand+= "\"";

    cout << youtubeDownloader::linkCommand.toStdString() << endl;
    return linkCommand;
}


void youtubeDownloader::embedCoverImage() {
    QDir dir(youtubeDownloader::musicFolder + "/" + youtubeDownloader::playlistNameTemp);
    QStringList audioFiles = dir.entryList(QStringList() << "*.mp3", QDir::Files);
    foreach (QString audioFile, audioFiles) {
        QString baseName = audioFile.left(audioFile.lastIndexOf('.'));
        QString imageFile = baseName + ".jpg";

        if (dir.exists(imageFile)) {
            QString audioFilePath = dir.absoluteFilePath(audioFile);    //Video name + path
            QString imageFilePath = dir.absoluteFilePath(imageFile);
            QString tempAudioFilePath = dir.absoluteFilePath(baseName + "_temp.mp3");
            QString outputAudioFilePath = audioFilePath;  // The final output path will be the same as the original audio file path

            // Rename the original audio file to a temporary name
            if (QFile::rename(audioFilePath, tempAudioFilePath)) {
                qDebug() << "Successfully renamed" << audioFile << "to" << baseName + "_temp.mp3";

                QProcess process;

                QString temp = youtubeDownloader::formatLinkCommand(tempAudioFilePath,imageFilePath, outputAudioFilePath);
                process.startCommand(temp);
                process.waitForFinished();
                if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
                    qDebug() << "Successfully embedded cover for" << audioFile;

                    // Remove the temporary audio file
                    if(QFile::remove(tempAudioFilePath)){
                        qDebug() << "Successfully removed temp audio file" << tempAudioFilePath;
                    }

                    if(QFile::remove(imageFilePath)){
                        qDebug() << "Successfully removed thumbnail file" << imageFilePath;
                    }
                } else {
                    qDebug() << "Failed to embed cover for" << audioFile;
                    qDebug() << process.readAllStandardError();

                    // Restore the original file if embedding fails
                    QFile::rename(tempAudioFilePath, audioFilePath);
                }
            } else {
                qDebug() << "Failed to rename" << audioFile << "to" << baseName + "_temp.mp3";
            }
        } else {
            qDebug() << "No cover image found for" << audioFile;
        }
    }
    emit progressBarValueChanged(100);
}
