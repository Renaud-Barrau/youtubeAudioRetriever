#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_downloadButton_clicked()
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

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    cout << arg1 << endl;
}

void MainWindow::on_saveParamsButton_clicked()
{
    cout << "Save params button pressed" << endl;
    QString apiKeyText = ui->apiKeyTextEdit->toPlainText();
    QString clientIdText = ui->clientIdTextEdit->toPlainText();
    QString clientSecretText = ui->clientSecretCodeTextEdit->toPlainText();
    QString refreshTokenText = ui->refreshTokenTextEdit->toPlainText();

    emit saveButtonPressed("apiKey",apiKeyText);
    emit saveButtonPressed("clientId",clientIdText);
    emit saveButtonPressed("clientSecretCode",clientSecretText);
    emit saveButtonPressed("refreshToken",refreshTokenText);

}

void MainWindow::receivedParamStartup(QString key, QString value){
    if(key == "apiKey"){
        ui->apiKeyTextEdit->insertPlainText(value);
    }
    else if(key == "clientId"){
        ui->clientIdTextEdit->insertPlainText(value);
    }
    else if(key == "clientSecretCode"){
        ui->clientSecretCodeTextEdit->insertPlainText(value);
    }
    else if(key == "refreshToken"){
        ui->refreshTokenTextEdit->insertPlainText(value);
    }
    else if(key == "musicFolder"){
        ui->musicFolderRepository->setText(value);
    }
    else if(key == "ffpmegPath"){
        ui->ffpmegPath->setText(value);
    }
    else if(key == "videoNumber"){
        ui->videoNumberTextEdit->setText(value);
    }
    else{
        cout << " [-] " << "Error in MainWindow::receivedParam(QString key, QString value)" << endl;
        cout << " --> " << "unknown key" << endl;
    }

}

void MainWindow::on_lockApiSettingsCheckBox_stateChanged(int arg1)
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

void MainWindow::on_locateMusicFolderButton_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un dossier", "", QFileDialog::ShowDirsOnly);
     // Vérifier si un dossier a été sélectionné
     if (!folderPath.isEmpty()) {
        cout << "Chemin sélectionné : " << folderPath.toStdString() << endl;
        ui->musicFolderRepository->setText(folderPath);
        emit locateMusicFolderButtonPressed("musicFolder", folderPath);
     }
     else{
         cout << "Error while selecting folder" << endl;
     }
}

void MainWindow::on_locateFfpmegButton_clicked()
{
    QString ffpmegPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un fichier", "", QFileDialog::ShowDirsOnly);
        // Vérifier si un fichier a été sélectionné
        if (!ffpmegPath.isEmpty()) {
        cout << "Chemin sélectionné : " << ffpmegPath.toStdString() << endl;
        ui->ffpmegPath->setText(ffpmegPath);
        emit locateFfmpegPathButtonPressed("ffpmegPath", ffpmegPath);
    }
    else{
        cout << "Error while selecting folder" << endl;
    }
}

void MainWindow::updateProgressBarValue(int value){
    ui->downloadProgressBar->setValue(value);
}

void MainWindow::on_playlistSelectionComboBox_activated(int index)
{
    cout << "selected playlist index : " << index << endl;
    emit playlistIndex(index);
}

void MainWindow::updatePlaylistList(QVector<QString> playlistNameArray,QVector<QString> playlistIdArray){
    cout << ui->playlistSelectionComboBox->currentIndex() << endl;
    for(int i = 0; i < playlistNameArray.size(); ++i){
        if(ui->playlistSelectionComboBox->findText(playlistNameArray.at(i)) == -1){
            ui->playlistSelectionComboBox->addItem(playlistNameArray.at(i));
        }
    }
    cout << ui->playlistSelectionComboBox->currentIndex() << endl;
    emit playlistIndex(0);
}

void MainWindow::on_fetchPlaylistButton_clicked()
{
    cout << "fetch playlist button pressed " << endl;
    emit requestSourceDeclarator("fetchPlaylists");

    // for YouTubeAPI
    emit requestParam("apiKey");
    emit requestParam("clientId");
    emit requestParam("clientSecretCode");
    emit requestParam("refreshToken");

    emit fetchPlaylistButtonPressed();

}

void MainWindow::videoNumberEnterPressed(){

}

void MainWindow::on_videoNumberTextEdit_textChanged()
{
    if(ui->videoNumberTextEdit->toPlainText().endsWith('\n')){
        if(1 <= ui->videoNumberTextEdit->toPlainText().toInt() && ui->videoNumberTextEdit->toPlainText().toInt() <= 50 ){
            cout << "video number selected is : " << ui->videoNumberTextEdit->toPlainText().toStdString() << endl;
            QString textTemp = ui->videoNumberTextEdit->toPlainText();
            textTemp.chop(1);
            emit saveVideoNumber("videoNumber",textTemp);

        }
        else{
            cout << "number must be between 1 and 50" << endl;
        }
        QString text = ui->videoNumberTextEdit->toPlainText();
        text.chop(1);
        ui->videoNumberTextEdit->setPlainText(text);

    }
}

void MainWindow::on_playPauseButton_clicked()
{
    emit playPauseButtonPressed();
}

void MainWindow::updateSliderValue(int value){
    ui->musicProressSlider->setValue(value);
}
