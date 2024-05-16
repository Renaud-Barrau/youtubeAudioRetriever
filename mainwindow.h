#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QTreeView>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QMovie>

#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    // void downloadButtonPressed(QString,QString,QString);
    void downloadButtonPressed();
    void saveButtonPressed(QString,QString);
    void locateMusicFolderButtonPressed(QString,QString);
    void locateFfmpegPathButtonPressed(QString,QString);
    void fetchPlaylistButtonPressed();
    void requestSourceDeclarator(QString);
    void playlistIndex(int);
    void requestParam(QString);
    void saveVideoNumber(QString,QString);
    void playPauseButtonPressed();




private slots:
    void on_downloadButton_clicked();
    void on_checkBox_stateChanged(int arg1);

    void on_saveParamsButton_clicked();

    void receivedParamStartup(QString,QString);

    void on_lockApiSettingsCheckBox_stateChanged(int arg1);

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

private:

};

#endif // MAINWINDOW_H
