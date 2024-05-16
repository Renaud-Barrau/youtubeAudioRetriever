/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSlider *musicProressSlider;
    QWidget *ApiFrame;
    QTextEdit *apiKeyTextEdit;
    QLabel *apiKeyLabel;
    QPushButton *saveParamsButton;
    QLabel *clientIdLabel;
    QTextEdit *clientIdTextEdit;
    QLabel *clientSecretLabel;
    QTextEdit *clientSecretCodeTextEdit;
    QTextEdit *refreshTokenTextEdit;
    QLabel *refreshTokenLabel;
    QCheckBox *lockApiSettingsCheckBox;
    QWidget *downloadFrame;
    QPushButton *downloadButton;
    QCheckBox *checkBox;
    QProgressBar *downloadProgressBar;
    QLabel *musicFolderLabel;
    QLabel *musicFolderRepository;
    QPushButton *locateMusicFolderButton;
    QLabel *ytdlpLabel;
    QLabel *ffpmegPath;
    QPushButton *locateFfpmegButton;
    QPushButton *fetchPlaylistButton;
    QComboBox *playlistSelectionComboBox;
    QTextEdit *videoNumberTextEdit;
    QFrame *line_3;
    QFrame *line;
    QFrame *line_2;
    QLabel *thumbnailImageLabel;
    QTreeView *treeView;
    QPushButton *playPauseButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1019, 697);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        musicProressSlider = new QSlider(centralwidget);
        musicProressSlider->setObjectName("musicProressSlider");
        musicProressSlider->setGeometry(QRect(30, 530, 741, 21));
        musicProressSlider->setCursor(QCursor(Qt::PointingHandCursor));
        musicProressSlider->setPageStep(1);
        musicProressSlider->setValue(50);
        musicProressSlider->setOrientation(Qt::Horizontal);
        ApiFrame = new QWidget(centralwidget);
        ApiFrame->setObjectName("ApiFrame");
        ApiFrame->setGeometry(QRect(10, 0, 591, 171));
        apiKeyTextEdit = new QTextEdit(ApiFrame);
        apiKeyTextEdit->setObjectName("apiKeyTextEdit");
        apiKeyTextEdit->setGeometry(QRect(0, 10, 481, 26));
        apiKeyLabel = new QLabel(ApiFrame);
        apiKeyLabel->setObjectName("apiKeyLabel");
        apiKeyLabel->setGeometry(QRect(490, 10, 49, 26));
        saveParamsButton = new QPushButton(ApiFrame);
        saveParamsButton->setObjectName("saveParamsButton");
        saveParamsButton->setGeometry(QRect(210, 140, 80, 24));
        clientIdLabel = new QLabel(ApiFrame);
        clientIdLabel->setObjectName("clientIdLabel");
        clientIdLabel->setGeometry(QRect(490, 40, 49, 26));
        clientIdTextEdit = new QTextEdit(ApiFrame);
        clientIdTextEdit->setObjectName("clientIdTextEdit");
        clientIdTextEdit->setGeometry(QRect(0, 40, 481, 26));
        clientSecretLabel = new QLabel(ApiFrame);
        clientSecretLabel->setObjectName("clientSecretLabel");
        clientSecretLabel->setGeometry(QRect(490, 70, 101, 26));
        clientSecretLabel->setAutoFillBackground(false);
        clientSecretLabel->setScaledContents(false);
        clientSecretLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        clientSecretLabel->setWordWrap(false);
        clientSecretCodeTextEdit = new QTextEdit(ApiFrame);
        clientSecretCodeTextEdit->setObjectName("clientSecretCodeTextEdit");
        clientSecretCodeTextEdit->setGeometry(QRect(0, 70, 481, 26));
        refreshTokenTextEdit = new QTextEdit(ApiFrame);
        refreshTokenTextEdit->setObjectName("refreshTokenTextEdit");
        refreshTokenTextEdit->setGeometry(QRect(0, 100, 481, 26));
        refreshTokenLabel = new QLabel(ApiFrame);
        refreshTokenLabel->setObjectName("refreshTokenLabel");
        refreshTokenLabel->setGeometry(QRect(490, 100, 91, 26));
        refreshTokenLabel->setAutoFillBackground(false);
        refreshTokenLabel->setScaledContents(false);
        refreshTokenLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        refreshTokenLabel->setWordWrap(false);
        lockApiSettingsCheckBox = new QCheckBox(ApiFrame);
        lockApiSettingsCheckBox->setObjectName("lockApiSettingsCheckBox");
        lockApiSettingsCheckBox->setGeometry(QRect(10, 140, 101, 22));
        downloadFrame = new QWidget(centralwidget);
        downloadFrame->setObjectName("downloadFrame");
        downloadFrame->setGeometry(QRect(620, 0, 391, 311));
        downloadButton = new QPushButton(downloadFrame);
        downloadButton->setObjectName("downloadButton");
        downloadButton->setGeometry(QRect(10, 140, 101, 31));
        checkBox = new QCheckBox(downloadFrame);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(240, 140, 131, 22));
        downloadProgressBar = new QProgressBar(downloadFrame);
        downloadProgressBar->setObjectName("downloadProgressBar");
        downloadProgressBar->setGeometry(QRect(50, 190, 301, 16));
        downloadProgressBar->setValue(0);
        musicFolderLabel = new QLabel(downloadFrame);
        musicFolderLabel->setObjectName("musicFolderLabel");
        musicFolderLabel->setGeometry(QRect(0, 10, 71, 16));
        musicFolderRepository = new QLabel(downloadFrame);
        musicFolderRepository->setObjectName("musicFolderRepository");
        musicFolderRepository->setGeometry(QRect(0, 40, 381, 32));
        locateMusicFolderButton = new QPushButton(downloadFrame);
        locateMusicFolderButton->setObjectName("locateMusicFolderButton");
        locateMusicFolderButton->setGeometry(QRect(290, 10, 80, 24));
        ytdlpLabel = new QLabel(downloadFrame);
        ytdlpLabel->setObjectName("ytdlpLabel");
        ytdlpLabel->setGeometry(QRect(0, 80, 71, 16));
        ffpmegPath = new QLabel(downloadFrame);
        ffpmegPath->setObjectName("ffpmegPath");
        ffpmegPath->setGeometry(QRect(0, 100, 381, 32));
        locateFfpmegButton = new QPushButton(downloadFrame);
        locateFfpmegButton->setObjectName("locateFfpmegButton");
        locateFfpmegButton->setGeometry(QRect(290, 80, 80, 24));
        fetchPlaylistButton = new QPushButton(downloadFrame);
        fetchPlaylistButton->setObjectName("fetchPlaylistButton");
        fetchPlaylistButton->setGeometry(QRect(10, 240, 101, 31));
        playlistSelectionComboBox = new QComboBox(downloadFrame);
        playlistSelectionComboBox->setObjectName("playlistSelectionComboBox");
        playlistSelectionComboBox->setGeometry(QRect(220, 240, 151, 28));
        videoNumberTextEdit = new QTextEdit(downloadFrame);
        videoNumberTextEdit->setObjectName("videoNumberTextEdit");
        videoNumberTextEdit->setGeometry(QRect(150, 140, 51, 26));
        line_3 = new QFrame(downloadFrame);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(0, 280, 381, 21));
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(600, 10, 20, 271));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(10, 170, 581, 31));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        thumbnailImageLabel = new QLabel(centralwidget);
        thumbnailImageLabel->setObjectName("thumbnailImageLabel");
        thumbnailImageLabel->setGeometry(QRect(800, 350, 121, 81));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName("treeView");
        treeView->setGeometry(QRect(150, 300, 371, 221));
        playPauseButton = new QPushButton(centralwidget);
        playPauseButton->setObjectName("playPauseButton");
        playPauseButton->setGeometry(QRect(360, 570, 83, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1019, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        apiKeyLabel->setText(QCoreApplication::translate("MainWindow", "API key", nullptr));
        saveParamsButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        clientIdLabel->setText(QCoreApplication::translate("MainWindow", "client ID", nullptr));
        clientSecretLabel->setText(QCoreApplication::translate("MainWindow", "client secret code", nullptr));
        refreshTokenLabel->setText(QCoreApplication::translate("MainWindow", "refresh token", nullptr));
        lockApiSettingsCheckBox->setText(QCoreApplication::translate("MainWindow", "Lock settings", nullptr));
        downloadButton->setText(QCoreApplication::translate("MainWindow", "Download", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "downloadOnStartup", nullptr));
        musicFolderLabel->setText(QCoreApplication::translate("MainWindow", "music folder : ", nullptr));
        musicFolderRepository->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        locateMusicFolderButton->setText(QCoreApplication::translate("MainWindow", "Locate", nullptr));
        ytdlpLabel->setText(QCoreApplication::translate("MainWindow", "ffpmeg path : ", nullptr));
        ffpmegPath->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        locateFfpmegButton->setText(QCoreApplication::translate("MainWindow", "Locate", nullptr));
        fetchPlaylistButton->setText(QCoreApplication::translate("MainWindow", "fetch playlist", nullptr));
        thumbnailImageLabel->setText(QCoreApplication::translate("MainWindow", "thumbnailImage", nullptr));
        playPauseButton->setText(QCoreApplication::translate("MainWindow", "play", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
