 #include <QApplication>
// #include <QmainWindow>
 #include <QVBoxLayout>
// #include <QQuickWidget>
#include <QDesktopServices>
#include <QTimer>
#include <QAudioOutput>
// #include <QtWebEngineWidgets>
#include <QWebEngineView>
#include <QmainWindow>
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

#include <youtubeApi.h>
// #include <audioreader.h>
#include <youtubeDownloader.h>
#include <mainWindow.h>
#include <paramfile.h>


using namespace std;





int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
//    youtubeApi youtube;
//    youtubeDownloader youtubeDownloader;
    // audioReader reader;
    mainWindow window;
//    paramFile paramFile("params.json");

    //TEMP
    // emit reader.sendDurationSignal(reader.player->duration());



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
//    QObject::connect(&youtube, SIGNAL(playlistListLoaded(QVector<QString>,QVector<QString>)), &window, SLOT(updatePlaylistList(QVector<QString>,QVector<QString>)));

//      window -> youtube
//    QObject::connect(&window, SIGNAL(downloadButtonPressed()), &youtube, SLOT(getToken()));
//    QObject::connect(&window, SIGNAL(fetchPlaylistButtonPressed()), &youtube, SLOT(getToken()));
//    QObject::connect(&window, SIGNAL(requestSourceDeclarator(QString)), &youtube, SLOT(updateRequestSource(QString)));
//    QObject::connect(&window, SIGNAL(playlistIndex(int)), &youtube, SLOT(updatePlaylistId(int)));

//      youtube -> youtubeDownloader
//    QObject::connect(&youtube, SIGNAL(videoDataLoaded(QVector<QString>,QVector<QString>,QVector<QString>,QString)), &youtubeDownloader, SLOT(downloadAll(QVector<QString>,QVector<QString>,QVector<QString>,QString)));

//      window -> paramFile
//    QObject::connect(&window, SIGNAL(saveButtonPressed(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));
//    QObject::connect(&window, SIGNAL(locateMusicFolderButtonPressed(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));
//    QObject::connect(&window, SIGNAL(locateFfmpegPathButtonPressed(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));
//    QObject::connect(&window, SIGNAL(saveVideoNumber(QString,QString)), &paramFile, SLOT(writeParam(QString,QString)));



    // Récupère le valeur dont la clé est passée en paramètre du signal
//    QObject::connect(&window, SIGNAL(requestParam(QString)), &paramFile, SLOT(readParam(QString)));




//                  RECEPTION DES DONNEES ISSUES DU PARAM FILE                  //
//      paramFile -> youtubeDownloader
//    QObject::connect(&paramFile, SIGNAL(paramValueReturn(QString,QString)), &youtubeDownloader, SLOT(updateParams(QString,QString)));

//      paramFile -> youtube
//    QObject::connect(&paramFile, SIGNAL(paramValueReturn(QString,QString)), &youtube, SLOT(updateParams(QString,QString)));

    //      paramFile -> window
//    QObject::connect(&paramFile, SIGNAL(paramValueReturn(QString,QString)), &window, SLOT(receivedParamStartup(QString,QString)));


//////////////////////////////////////////////////////////////////////////////////



//      youtubeDownloader -> window
//    QObject::connect(&youtubeDownloader, SIGNAL(progressBarUpdate(int)), &window, SLOT(updateProgressBarValue(int)));

    //      reader -> window
    // QObject::connect(&reader, SIGNAL(updateSliderValueSignal(int)),&window, SLOT(updateSliderValue(int)));
    // QObject::connect(&reader, SIGNAL(updateSliderRangeSignal(int)),&window, SLOT(updateSliderRange(int)));
    // QObject::connect(&reader, SIGNAL(updateMusicNameSignal(QUrl)),&window, SLOT(updateMusicLabel(QUrl)));




//    paramFile.readParam("apiKey");
//    emit paramFile.paramValueReturn("apiKey", paramFile.value);
//    youtube.Api = paramFile.value;

//    paramFile.readParam("clientId");
//    emit paramFile.paramValueReturn("clientId", paramFile.value);
//    youtube.clientId = paramFile.value;

//    paramFile.readParam("clientSecretCode");
//    emit paramFile.paramValueReturn("clientSecretCode", paramFile.value);
//    youtube.clientSecretCode = paramFile.value;

//    paramFile.readParam("refreshToken");
//    emit paramFile.paramValueReturn("refreshToken", paramFile.value);
//    youtube.refreshToken = paramFile.value;

//    paramFile.readParam("musicFolder");
//    emit paramFile.paramValueReturn("musicFolder", paramFile.value);
//    youtubeDownloader.musicFolder = paramFile.value;

//    paramFile.readParam("ffpmegPath");
//    emit paramFile.paramValueReturn("ffpmegPath", paramFile.value);
//    youtubeDownloader.ffmpegPath = paramFile.value;

//    paramFile.readParam("videoNumber");
//    emit paramFile.paramValueReturn("videoNumber", paramFile.value);
//    youtube.maxResults = paramFile.value.toInt();



//    emit youtube.playlistListLoaded(youtube.playlistNameArray,youtube.playlistIdArray);


//    paramFile.readParam("playlistSelectionIndex");
//    emit paramFile.loadParam("playlistSelectionIndex", paramFile.value);
//    youtubeDownloader.ffmpegPath = paramFile.value;


//    reader.playLocalAudio("C:/Users/rbarr/Desktop/FKJ - Go Back Home.webm");

//    youtubeDownloader.formatCommand();
//    youtubeDownloader.execCommand();


//     QmainWindow mainWindow;
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


