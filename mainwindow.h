#ifndef mainWindow_H
#define mainWindow_H

#include <QmainWindow>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QTreeView>
#include <QDesktopServices>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QMovie>
#include <QKeySequence>
#include <memory> // Pour std::shared_ptr

#include <iostream>

#include "apisettings.h"
#include "audioreader.h"
#include "paramfile.h"
#include <youtubeDownloader.h>
#include <youtubeapi.h>
#include <ressourcepaths.h>

using namespace std;

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:

    Ui::mainWindow *ui;

    std::shared_ptr<paramFile> paramFileObject;
    std::shared_ptr<youtubeDownloader> youtubeDownloaderObject;
    std::shared_ptr<youtubeApi> youtubeApiObject;
    std::shared_ptr<audioReader> audioReaderObject;
    std::shared_ptr<apiSettings> apiSettingsObject;
    std::shared_ptr<ressourcePaths> ressourcePathsObject;

    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();



private slots:
    void on_downloadButton_clicked();
    void on_checkBox_stateChanged(int arg1);

    // void on_saveParamsButton_clicked();

    // void on_lockApiSettingsCheckBox_stateChanged(int arg1);

    void on_locateMusicFolderButton_clicked();

    void on_locateFfpmegButton_clicked();

    void updateProgressBarValue(int);

    void on_playlistSelectionComboBox_activated(int index);

    void updatePlaylistList(QVector<QString>,QVector<QString>);

    void on_fetchPlaylistButton_clicked();

    void videoNumberEnterPressed();



    void on_videoNumberTextEdit_textChanged();

    void on_playPauseButton_clicked();

    void updateSliderValue(int value);

    void updateSliderRange(int value);

    void updateMusicLabel(QUrl musicName);

    void on_apiCredentials_triggered();
    void on_ressourcePaths_triggered();

    void on_aboutThisProject_triggered();
    void on_aboutQt_triggered();





    void on_musicProgressSlider_sliderMoved(int value);




private:

};

#endif // mainWindow_H
