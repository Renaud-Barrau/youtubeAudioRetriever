#include "audioreader.h"




void audioReader::playYouTubeVideo(const QString &videoUrl){
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    //QUrl lienVideo("https://www.youtube.com/watch?v=D_nnzo9feT0");
    player->setAudioOutput(audioOutput);
    // player->setSource(QUrl::fromLocalFile("C:/Users/rbarr/Desktop/joyeux anniversaire Manon !/émotion.wav"));
    player->setSource(videoUrl);
    // audioOutput->setVolume(0.1);
    player->play();
}

void audioReader::playLocalAudio(const QString &filePath){
    audioReader::player->setAudioOutput(&audioOutput);
    audioReader::player->setSource(filePath);
    // audioOutput->setVolume(0.1);
    audioReader::player->play();
    cout << "lecture" << endl;
}

void audioReader::togglePlayback() {
    cout << audioReader::player->playbackState() << endl;
    if (audioReader::player->playbackState() == QMediaPlayer::PlayingState) {
        audioReader::player->pause();
        audioReader::positionTimer->stop();
        cout << "Pause" << endl;
    } else {
        audioReader::player->play();
        audioReader::positionTimer->start(1000);
        cout << "Play" << endl;
    }
}

void audioReader::changeAudio(QString path){
    audioReader::player->setSource(path);
}

void audioReader::setPosition(int position){
    // position in miliseconds
    audioReader::player->setPosition(position);
}

void audioReader::updateSliderValue(){
    cout << audioReader::player->position() << endl;

}
