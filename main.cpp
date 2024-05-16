 #include <QApplication>
// #include <QMainWindow>
 #include <QVBoxLayout>
// #include <QQuickWidget>
#include <QDesktopServices>
#include <QTimer>
#include <QAudioOutput>
// #include <QtWebEngineWidgets>
#include <QWebEngineView>
#include <QMainWindow>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QTextEdit>

#include <iostream>
#include <cstdlib>
#include <sstream>
// #include <unistd.h>

#include <windows.h>
#include <string>
#include <shellapi.h>

#include <youtubeapi.h>
#include <audioreader.h>
#include <youtubedownloader.h>
#include <mainwindow.h>
#include <paramfile.h>


using namespace std;





int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    YouTubeAPI youtube;
    youtubedownloader youtubeDownloader;
    audioReader reader;
    MainWindow window;
    paramFile paramFile("params.json");




    // Écrire une valeur
    // if (paramFile.writeParam("example_key", "new_value")) {
    //     cout << "Value written" << endl;
    // }
    // QString value;
    // if(paramFile.readParam("examzefzezefple_key")){
    //     cout << paramFile.value.toStdString() << endl;
    // }


//////////      CONNECT     //////////

//      youtube -> window
    QObject::connect(&youtube, SIGNAL(playlistListLoaded(QVector<QString>,QVector<QString>)), &window, SLOT(updatePlaylistList(QVector<QString>,QVector<QString>)));

//      window -> youtube
    QObject::connect(&window, SIGNAL(downloadButtonPressed()), &youtube, SLOT(getToken()));
    QObject::connect(&window, SIGNAL(fetchPlaylistButtonPressed()), &youtube, SLOT(getToken()));
    QObject::connect(&window, SIGNAL(requestSourceDeclarator(QString)), &youtube, SLOT(updateRequestSource(QString)));
    QObject::connect(&window, SIGNAL(playlistIndex(int)), &youtube, SLOT(updatePlaylistId(int)));

//      youtube -> youtubeDownloader
    QObject::connect(&youtube, SIGNAL(videoDataLoaded(QVector<QString>,QVector<QString>,QVector<QString>,QString)), &youtubeDownloader, SLOT(downloadAll(QVector<QString>,QVector<QString>,QVector<QString>,QString)));

//      window -> paramFile
    QObject::connect(&window, SIGNAL(saveButtonPressed(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));
    QObject::connect(&window, SIGNAL(locateMusicFolderButtonPressed(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));
    QObject::connect(&window, SIGNAL(locateFfmpegPathButtonPressed(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));
    QObject::connect(&window, SIGNAL(saveVideoNumber(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));

//      window -> reader
    QObject::connect(&window, SIGNAL(playPauseButtonPressed()), &reader, SLOT(togglePlayback()));


    // Récupère le valeur dont la clé est passée en paramètre du signal
    QObject::connect(&window, SIGNAL(requestParam(QString)), &paramFile, SLOT(readParam(QString)));

//      paramFile -> window
    QObject::connect(&paramFile, SIGNAL(loadParam(QString,QString)), &window, SLOT(receivedParamStartup(QString,QString)));


//                  RECEPTION DES DONNEES ISSUES DU PARAM FILE                  //
//      paramFile -> youtubeDownloader
    QObject::connect(&paramFile, SIGNAL(paramValueReturn(QString,QString)), &youtubeDownloader, SLOT(updateParams(QString,QString)));

//      paramFile -> youtube
    QObject::connect(&paramFile, SIGNAL(paramValueReturn(QString,QString)), &youtube, SLOT(updateParams(QString,QString)));
//////////////////////////////////////////////////////////////////////////////////



//      youtubeDownloader -> window
    QObject::connect(&youtubeDownloader, SIGNAL(progressBarUpdate(int)), &window, SLOT(updateProgressBarValue(int)));





    paramFile.readParam("apiKey");
    emit paramFile.loadParam("apiKey", paramFile.value);
    youtube.Api = paramFile.value;

    paramFile.readParam("clientId");
    emit paramFile.loadParam("clientId", paramFile.value);
    youtube.clientId = paramFile.value;

    paramFile.readParam("clientSecretCode");
    emit paramFile.loadParam("clientSecretCode", paramFile.value);
    youtube.clientSecretCode = paramFile.value;

    paramFile.readParam("refreshToken");
    emit paramFile.loadParam("refreshToken", paramFile.value);
    youtube.refreshToken = paramFile.value;

    paramFile.readParam("musicFolder");
    emit paramFile.loadParam("musicFolder", paramFile.value);
    youtubeDownloader.musicFolder = paramFile.value;

    paramFile.readParam("ffpmegPath");
    emit paramFile.loadParam("ffpmegPath", paramFile.value);
    youtubeDownloader.ffmpegPath = paramFile.value;

    paramFile.readParam("videoNumber");
    emit paramFile.loadParam("videoNumber", paramFile.value);
    youtube.maxResults = paramFile.value.toInt();



//    emit youtube.playlistListLoaded(youtube.playlistNameArray,youtube.playlistIdArray);


//    paramFile.readParam("playlistSelectionIndex");
//    emit paramFile.loadParam("playlistSelectionIndex", paramFile.value);
//    youtubeDownloader.ffmpegPath = paramFile.value;


//    reader.playLocalAudio("C:/Users/rbarr/Desktop/FKJ - Go Back Home.webm");

//    youtubeDownloader.formatCommand();
//    youtubeDownloader.execCommand();


//     QMainWindow mainWindow;
    // QWebEngineView *view = new QWebEngineView(&mainWindow);
    // view->setUrl(QUrl("https://www.youtube.com/watch?v=D_nnzo9feT0"));
    // mainWindow.setCentralWidget(view);
//     mainWindow.show();
    // window.setStyleSheet("background-color: white;");

    window.show();

    // youtube.getToken(youtube.clientId, youtube.clientSecretCode, youtube.refreshToken);



    //youtube.fetchPlaylists(youtube.Api, youtube.accessToken);
    //youtube.printToken();
//    return 0;
//    youtube.checkTokenInfo(youtube.accessToken);
    return a.exec();

}


