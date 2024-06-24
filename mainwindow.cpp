#include "mainWindow.h"
#include "ui_mainWindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow),
    paramFileObject(std::make_shared<paramFile>("params.json")),
    youtubeDownloaderObject(std::make_shared<youtubeDownloader>()),
    youtubeApiObject(std::make_shared<youtubeApi>()),
    audioReaderObject(std::make_shared<audioReader>()),
    apiSettingsObject(std::make_shared<apiSettings>(paramFileObject)),
    ressourcePathsObject(std::make_shared<ressourcePaths>(paramFileObject))


{
    ui->setupUi(this);



    QObject::connect(audioReaderObject.get(), SIGNAL(updateSliderValueSignal(int)),this, SLOT(updateSliderValue(int)));
    QObject::connect(audioReaderObject.get(), SIGNAL(updateSliderRangeSignal(int)),this, SLOT(updateSliderRange(int)));
    QObject::connect(audioReaderObject.get(), SIGNAL(updateMusicNameSignal(QUrl)), this, SLOT(updateMusicLabel(QUrl)));

    QObject::connect(youtubeApiObject.get(), SIGNAL(playlistListLoaded(QVector<QString>,QVector<QString>)), this, SLOT(updatePlaylistList(QVector<QString>,QVector<QString>)));
    QObject::connect(youtubeApiObject.get(), SIGNAL(videoDataLoaded(QVector<QString>,QVector<QString>,QVector<QString>, QString)), youtubeDownloaderObject.get(), SLOT(downloadAll(QVector<QString>,QVector<QString>,QVector<QString>, QString)));

    QObject::connect(youtubeDownloaderObject.get(),  SIGNAL(progressBarValueChanged(int)), this, SLOT(updateProgressBarValue(int)));

//////////          DOWNLOAD FRAME           //////////

    // ui->musicFolderRepository->setText(paramFileObject->readParam("musicFolder"));
    // ui->ffpmegPath->setText(paramFileObject->readParam("ffmpegPath"));
    // ui->musicFolderRepository->setWordWrap(true);
    // ui->ffpmegPath->setWordWrap(true);

    ui->videoNumberTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->videoNumberTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->videoNumberTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//          //
    QSize labelSize = ui->thumbnailImageLabel->size();
    QPixmap image("C:/Users/rbarr/Desktop/musique_test/Lika Morgan - In Motion.webp");
    QPixmap scaledPixmap = image.scaled(labelSize,Qt::KeepAspectRatio);
    ui->thumbnailImageLabel->setPixmap(scaledPixmap);


    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(paramFileObject->readParam("musicFolder"));

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(paramFileObject->readParam("musicFolder")));



    ui->playlistSelectionComboBox->setCurrentIndex(0);
    ui->videoNumberTextEdit->setPlainText(paramFileObject->readParam("videoNumber"));



}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::on_downloadButton_clicked()
{
    qInfo() << "Download button pressed";
    if(youtubeApiObject->requestSource == "fetchPlaylists" || youtubeApiObject->requestSource == "fetchPlaylistElements"){

    youtubeApiObject->requestSource = "fetchPlaylistElements";
    youtubeDownloaderObject->musicFolder = paramFileObject->readParam("musicFolder");
    youtubeDownloaderObject->ffmpegPath = paramFileObject->readParam("ffmpegPath");
    youtubeApiObject->maxResults = paramFileObject->readParam("videoNumber").toInt();
    cout << "Download button pressed" << endl;
    qInfo() << "Params fetched, going for Token request";
    youtubeApiObject->getToken();
    }
    else{
        qCritical() << "requestSource should be either \"fetchPlaylists\" or \"fetchPlaylistElements\"";
        return;
    }

}

void mainWindow::on_checkBox_stateChanged(int arg1)
{
    cout << arg1 << endl;
}


void mainWindow::updateProgressBarValue(int value){
    ui->downloadProgressBar->setValue(value);
}

void mainWindow::on_playlistSelectionComboBox_activated(int index)
{
    cout << "selected playlist index : " << index << endl;
    qInfo() << "selected playlist index : " << index;
    youtubeApiObject->playlistId = youtubeApiObject->playlistIdArray.at(index);
    youtubeApiObject->playlistName = youtubeApiObject->playlistNameArray.at(index);
    // emit playlistIndex(index);
}

void mainWindow::updatePlaylistList(QVector<QString> playlistNameArray,QVector<QString> playlistIdArray){
    cout << ui->playlistSelectionComboBox->currentIndex() << endl;
    for(int i = 0; i < youtubeApiObject->playlistNameArray.size(); ++i){
        if(ui->playlistSelectionComboBox->findText(youtubeApiObject->playlistNameArray.at(i)) == -1){
            ui->playlistSelectionComboBox->addItem(youtubeApiObject->playlistNameArray.at(i));
        }
    }
    cout << ui->playlistSelectionComboBox->currentIndex() << endl;
    youtubeApiObject->playlistId = youtubeApiObject->playlistIdArray.at(0);
    youtubeApiObject->playlistName = youtubeApiObject->playlistNameArray.at(0);
}

void mainWindow::on_fetchPlaylistButton_clicked()
{
    cout << "fetch playlist button pressed " << endl;
    qInfo() << "fetch playlist button pressed " ;

    youtubeApiObject->requestSource = "fetchPlaylists";

    youtubeApiObject->Api = paramFileObject->readParam("apiKey");
    youtubeApiObject->clientId = paramFileObject->readParam("clientId");
    youtubeApiObject->clientSecretCode = paramFileObject->readParam("clientSecretCode");
    youtubeApiObject->refreshToken = paramFileObject->readParam("refreshToken");

    qInfo() << "Params fetched, going for Token request";
    youtubeApiObject->getToken();

}

void mainWindow::videoNumberEnterPressed(){

}

void mainWindow::on_videoNumberTextEdit_textChanged()
{
    if(ui->videoNumberTextEdit->toPlainText().endsWith('\n')){
        if(1 <= ui->videoNumberTextEdit->toPlainText().toInt() && ui->videoNumberTextEdit->toPlainText().toInt() <= 50 ){
            cout << "video number selected is : " << ui->videoNumberTextEdit->toPlainText().toStdString() << endl;
            QString textTemp = ui->videoNumberTextEdit->toPlainText();
            textTemp.chop(1);
//            emit saveVideoNumber("videoNumber",textTemp);
            paramFileObject->writeParam("videoNumber",textTemp);
            qInfo() << "VideoNumber saved";


        }
        else{
            cout << "number must be between 1 and 50" << endl;
            qCritical() << "number must be between 1 and 50";
        }
        QString text = ui->videoNumberTextEdit->toPlainText();
        text.chop(1);
        ui->videoNumberTextEdit->setPlainText(text);

    }
    // else{
    //     qCritical() << "Wrong format for videoNumberTextEdit : should end with \\n";
    // }
}

void mainWindow::on_playPauseButton_clicked()
{
    audioReaderObject->togglePlayback();
}

void mainWindow::updateSliderValue(int value){
    ui->musicProgressSlider->setValue(value);
}

void mainWindow::updateSliderRange(int value){
    ui->musicProgressSlider->setRange(0, value);
}

void mainWindow::updateMusicLabel(QUrl musicName){
    ui->musicNameLabel->setText(musicName.toString());
}



void mainWindow::on_musicProgressSlider_sliderMoved(int value){
    audioReaderObject->setPosition(value);
}



void mainWindow::on_apiCredentials_triggered(){
    apiSettingsObject->exec();
}

void mainWindow::on_ressourcePaths_triggered(){
    ressourcePathsObject->exec();
}


void mainWindow::on_aboutThisProject_triggered(){
    qInfo() << "aboutThisProject button pressed";
    QUrl url("https://renaud-barrau.github.io/youtubeAudioRetriever/docs/html/index.html");
    if(QDesktopServices::openUrl(url)){
        qInfo() << "aboutThisProject web page opened";
    }
    else{
        qCritical() << "failed to open web link";
    }

}
void mainWindow::on_aboutQt_triggered(){
    qInfo() << "aboutQt button pressed";
    QUrl url("https://www.qt.io/");
    if(QDesktopServices::openUrl(url)){
        qInfo() << "aboutQt web page opened";
    }
    else{
        qCritical() << "failed to open web link";
    }
}

void mainWindow::on_logs_triggered(){
    qInfo() << "Logs button pressed";
    QUrl url = QUrl::fromLocalFile(QCoreApplication::applicationDirPath());
    if(QDesktopServices::openUrl(url)){
        qInfo() << "Succefully opened file explorerto logs folder";
    }
    else{
        qCritical() << "failed to open file explorer";
    }
}
