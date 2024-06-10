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
    ressourcePathsObject(std::make_shared<ressourcePaths>())


{
    ui->setupUi(this);



    QObject::connect(audioReaderObject.get(), SIGNAL(updateSliderValueSignal(int)),this, SLOT(updateSliderValue(int)));
    QObject::connect(audioReaderObject.get(), SIGNAL(updateSliderRangeSignal(int)),this, SLOT(updateSliderRange(int)));
    QObject::connect(audioReaderObject.get(), SIGNAL(updateMusicNameSignal(QUrl)), this, SLOT(updateMusicLabel(QUrl)));

    QObject::connect(youtubeApiObject.get(), SIGNAL(playlistListLoaded(QVector<QString>,QVector<QString>)), this, SLOT(updatePlaylistList(QVector<QString>,QVector<QString>)));
    QObject::connect(youtubeApiObject.get(), SIGNAL(videoDataLoaded(QVector<QString>,QVector<QString>,QVector<QString>, QString)), youtubeDownloaderObject.get(), SLOT(downloadAll(QVector<QString>,QVector<QString>,QVector<QString>, QString)));



//////////          DOWNLOAD FRAME           //////////

    ui->musicFolderRepository->setText(paramFileObject->readParam("musicFolder"));
    ui->ffpmegPath->setText(paramFileObject->readParam("ffmpegPath"));
    ui->musicFolderRepository->setWordWrap(true);
    ui->ffpmegPath->setWordWrap(true);

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



//    ui->playlistSelectionComboBox->addItem("elem1");
//    ui->playlistSelectionComboBox->addItem("elem2");
//    ui->playlistSelectionComboBox->addItem("elem3");

    ui->playlistSelectionComboBox->setCurrentIndex(0);

}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::on_downloadButton_clicked()
{
    if(youtubeApiObject->requestSource == "fetchPlaylists" || youtubeApiObject->requestSource == "fetchPlaylistElements"){

    youtubeApiObject->requestSource = "fetchPlaylistElements";
    youtubeDownloaderObject->musicFolder = paramFileObject->readParam("musicFolder");
    youtubeDownloaderObject->ffmpegPath = paramFileObject->readParam("ffmpegPath");
    youtubeApiObject->maxResults = paramFileObject->readParam("videoNumber").toInt();
    cout << "Download button pressed" << endl;
    youtubeApiObject->getToken();
    }
    else{
        return;
    }

}

void mainWindow::on_checkBox_stateChanged(int arg1)
{
    cout << arg1 << endl;
}



void mainWindow::on_locateMusicFolderButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un dossier", "", QFileDialog::ShowDirsOnly);
     // Vérifier si un dossier a été sélectionné
     if (!folderPath.isEmpty()) {
        cout << "Chemin sélectionné : " << folderPath.toStdString() << endl;
        ui->musicFolderRepository->setText(folderPath);
        paramFileObject->writeParam("musicFolder", folderPath);
     }
     else{
         cout << "Error while selecting folder" << endl;
     }
}

void mainWindow::on_locateFfpmegButton_clicked()
{
    QString ffpmegPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un fichier", "", QFileDialog::ShowDirsOnly);
        if (!ffpmegPath.isEmpty()) {
        cout << "Chemin sélectionné : " << ffpmegPath.toStdString() << endl;
        ui->ffpmegPath->setText(ffpmegPath);
        paramFileObject->writeParam("ffmpegPath", ffpmegPath);
    }
    else{
        cout << "Error while selecting folder" << endl;
    }
}

void mainWindow::updateProgressBarValue(int value){
    ui->downloadProgressBar->setValue(value);
}

void mainWindow::on_playlistSelectionComboBox_activated(int index)
{
    cout << "selected playlist index : " << index << endl;
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
    youtubeApiObject->requestSource = "fetchPlaylists";

    youtubeApiObject->Api = paramFileObject->readParam("apiKey");
    youtubeApiObject->clientId = paramFileObject->readParam("clientId");
    youtubeApiObject->clientSecretCode = paramFileObject->readParam("clientSecretCode");
    youtubeApiObject->refreshToken = paramFileObject->readParam("refreshToken");

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


        }
        else{
            cout << "number must be between 1 and 50" << endl;
        }
        QString text = ui->videoNumberTextEdit->toPlainText();
        text.chop(1);
        ui->videoNumberTextEdit->setPlainText(text);

    }
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
    QUrl url("https://renaud-barrau.github.io/youtubeAudioRetriever/docs/html/index.html");
    QDesktopServices::openUrl(url);
}
void mainWindow::on_aboutQt_triggered(){
    QUrl url("https://www.qt.io/");
    QDesktopServices::openUrl(url);
}
