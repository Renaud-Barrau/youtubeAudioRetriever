#include "ressourcepaths.h"
#include "ui_ressourcepaths.h"

ressourcePaths::ressourcePaths(std::shared_ptr<paramFile> paramFilePtr)
    :
    ui(new Ui::ressourcePaths),
    paramFileObject(paramFilePtr)
{
    ui->setupUi(this);
    ui->musicFolderRepository->setWordWrap(true);
    ui->ffmpegPath->setWordWrap(true);
    ui->musicFolderRepository->setText(paramFileObject->readParam("musicFolder"));
    ui->ffmpegPath->setText(paramFileObject->readParam("ffmpegPath"));

}

ressourcePaths::~ressourcePaths()
{
    delete ui;
}


void ressourcePaths::on_locateMusicFolderButton_clicked()
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

void ressourcePaths::on_locateFfpmegButton_clicked()
{
    QString ffmpegPath = QFileDialog::getExistingDirectory(nullptr, "Sélectionner un fichier", "", QFileDialog::ShowDirsOnly);
        if (!ffmpegPath.isEmpty()) {
        cout << "Chemin sélectionné : " << ffmpegPath.toStdString() << endl;
        ui->ffmpegPath->setText(ffmpegPath);
        paramFileObject->writeParam("ffmpegPath", ffmpegPath);
    }
    else{
        cout << "Error while selecting folder" << endl;
    }
}
