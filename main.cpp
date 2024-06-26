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

// #include <iostream>
// #include <cstdlib>
// #include <sstream>
// #include <unistd.h>

#include <windows.h>
#include <string>
#include <shellapi.h>

#include <youtubeApi.h>
// #include <audioreader.h>
#include <youtubeDownloader.h>
#include <mainWindow.h>
#include <paramfile.h>

#include <logHandler.h>


// using namespace std;





int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    logHandler::instance().init("applicationLog.log", 1024 * 1024, 5);
    qInfo() << "==========  Starting application    ==========";

    mainWindow window;
    QFile file("C:/Users/rbarr/Documents/GitHub/youtubeAudioRetriever/style.css");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close();
    }

    window.show();

    int result  = a.exec();

    qInfo() << "==========  Closing application    ==========";
    qInfo() << "\n";
    logHandler::instance().close();
    return result;


}


