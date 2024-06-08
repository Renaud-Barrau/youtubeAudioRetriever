#include "mainWindow.h"
#include "ui_mainWindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow),
    paramFileObject(std::make_shared<paramFile>("params.json")),
    apiSettingsObject(std::make_shared<apiSettings>())
{
    ui->setupUi(this);


    audioReaderObject = new audioReader(this);

    youtubeDownloaderObject = new youtubeDownloader(this);
    youtubeApiObject = new youtubeApi(this);



    QObject::connect(audioReaderObject, SIGNAL(updateSliderValueSignal(int)),this, SLOT(updateSliderValue(int)));
    QObject::connect(audioReaderObject, SIGNAL(updateSliderRangeSignal(int)),this, SLOT(updateSliderRange(int)));
    QObject::connect(audioReaderObject, SIGNAL(updateMusicNameSignal(QUrl)), this, SLOT(updateMusicLabel(QUrl)));
    // ui->apiCredentials->setShortcut(QKeySequence::New);



//////////          API FRAME           //////////

    ui->apiKeyTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->apiKeyTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->clientIdTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->clientIdTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->clientSecretCodeTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->clientSecretCodeTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->refreshTokenTextEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->refreshTokenTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->lockApiSettingsCheckBox->setCheckState(Qt::Checked);

    // SETUP TEXT EDIT AT STARTUP
    ui->apiKeyTextEdit->setPlainText(paramFileObject->readParam("apiKey"));
    ui->clientIdTextEdit->setPlainText(paramFileObject->readParam("clientId"));
    ui->clientSecretCodeTextEdit->setPlainText(paramFileObject->readParam("clientSecretCode"));
    ui->refreshTokenTextEdit->setPlainText(paramFileObject->readParam("refreshToken"));
    ui->musicFolderRepository->setText(paramFileObject->readParam("musicFolder"));
    ui->ffpmegPath->setText(paramFileObject->readParam("ffmpegPath"));


//////////          DOWNLOAD FRAME           //////////
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
    model->setRootPath(QDir::currentPath());

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(QDir::currentPath()));



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
    cout << "Download button pressed" << endl;
    emit requestSourceDeclarator("fetchPlaylistElements");
    // emit downloadButtonPressed(ui->clientIdTextEdit->toPlainText(),ui->clientSecretCodeTextEdit->toPlainText(),ui->refreshTokenTextEdit->toPlainText());

    // for youtubeDownloader
    emit requestParam("musicFolder");
    emit requestParam("ffpmegPath");

    // for YouTubeAPI
    emit requestParam("apiKey");
    emit requestParam("clientId");
    emit requestParam("clientSecretCode");
    emit requestParam("refreshToken");
    emit requestParam("videoNumber");
    emit downloadButtonPressed();
}

void mainWindow::on_checkBox_stateChanged(int arg1)
{
    cout << arg1 << endl;
}

void mainWindow::on_saveParamsButton_clicked()
{

    cout << "Save params button pressed" << endl;
    paramFileObject->writeParam("apiKey", ui->apiKeyTextEdit->toPlainText());
    paramFileObject->writeParam("clientId", ui->clientIdTextEdit->toPlainText());
    paramFileObject->writeParam("clientSecretCode", ui->clientSecretCodeTextEdit->toPlainText());
    paramFileObject->writeParam("refreshToken", ui->refreshTokenTextEdit->toPlainText());
}



void mainWindow::on_lockApiSettingsCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->apiKeyTextEdit->setReadOnly(false);
        ui->apiKeyTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
        ui->clientIdTextEdit->setReadOnly(false);
        ui->clientIdTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
        ui->clientSecretCodeTextEdit->setReadOnly(false);
        ui->clientSecretCodeTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
        ui->refreshTokenTextEdit->setReadOnly(false);
        ui->refreshTokenTextEdit->setStyleSheet("QTextEdit { color: #000000; }");
    }
    else if(arg1 == 2){
        ui->apiKeyTextEdit->setReadOnly(true);
        ui->apiKeyTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
        ui->clientIdTextEdit->setReadOnly(true);
        ui->clientIdTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
        ui->clientSecretCodeTextEdit->setReadOnly(true);
        ui->clientSecretCodeTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
        ui->refreshTokenTextEdit->setReadOnly(true);
        ui->refreshTokenTextEdit->setStyleSheet("QTextEdit { color: #808080; }");
    }
}

void mainWindow::on_locateMusicFolderButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un dossier", "", QFileDialog::ShowDirsOnly);
     // Vérifier si un dossier a été sélectionné
     if (!folderPath.isEmpty()) {
        cout << "Chemin sélectionné : " << folderPath.toStdString() << endl;
        ui->musicFolderRepository->setText(folderPath);
        paramFileObject->writeParam("musicFolder", folderPath);
//        emit locateMusicFolderButtonPressed("musicFolder", folderPath);
     }
     else{
         cout << "Error while selecting folder" << endl;
     }
}

void mainWindow::on_locateFfpmegButton_clicked()
{
    QString ffpmegPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un fichier", "", QFileDialog::ShowDirsOnly);
        // Vérifier si un fichier a été sélectionné
        if (!ffpmegPath.isEmpty()) {
        cout << "Chemin sélectionné : " << ffpmegPath.toStdString() << endl;
        ui->ffpmegPath->setText(ffpmegPath);
        paramFileObject->writeParam("ffmpegPath", ffpmegPath);
//        emit locateFfmpegPathButtonPressed("ffpmegPath", ffpmegPath);
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
    emit playlistIndex(index);
}

void mainWindow::updatePlaylistList(QVector<QString> playlistNameArray,QVector<QString> playlistIdArray){
    cout << ui->playlistSelectionComboBox->currentIndex() << endl;
    for(int i = 0; i < youtubeApiObject->playlistNameArray.size(); ++i){
        if(ui->playlistSelectionComboBox->findText(youtubeApiObject->playlistNameArray.at(i)) == -1){
            ui->playlistSelectionComboBox->addItem(youtubeApiObject->playlistNameArray.at(i));
        }
    }
    cout << ui->playlistSelectionComboBox->currentIndex() << endl;
//    emit playlistIndex(0);
    youtubeApiObject->playlistId = youtubeApiObject->playlistIdArray.at(0);
    youtubeApiObject->playlistName = youtubeApiObject->playlistNameArray.at(0);
}

void mainWindow::on_fetchPlaylistButton_clicked()
{
    cout << "fetch playlist button pressed " << endl;
//    emit requestSourceDeclarator("fetchPlaylists");
    youtubeApiObject->requestSource = "fetchPlaylists";

    // for YouTubeAPI
//    emit requestParam("apiKey");
//    emit requestParam("clientId");
//    emit requestParam("clientSecretCode");
//    emit requestParam("refreshToken");
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

void mainWindow::on_apiCredentials_triggered(){
    apiSettingsObject = new apiSettings(paramFileObject);
    apiSettingsObject->exec();
}

void mainWindow::on_musicProgressSlider_sliderMoved(int value){
    audioReaderObject->setPosition(value);
}
