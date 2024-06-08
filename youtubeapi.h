#ifndef YOUTUBEAPI_H
#define YOUTUBEAPI_H


#include <QTimer>
#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QVector>


#include <iostream>

using namespace std;

class youtubeApi : public QObject
{
    Q_OBJECT
public:
////////////////////    CONSTRUCTEUR    ////////////////////
    explicit youtubeApi(QObject *parent = nullptr) : QObject(parent){
//        accessToken = "";

        timer->setInterval(refreshTime);
        timer->start();

        // Signal émit une fois que le access token a été chargé dans YouTubeAPI::accessToken -> lance le fetch des playlists
//        connect(this, SIGNAL(fetchPlaylistElementSignal()), this, SLOT(fetchPlaylistElements()));
//        connect(this, SIGNAL(fetchPlaylistsSignal()), this, SLOT(fetchPlaylists()));


        // Signal émit lorsque le timer arrive au bout de 1h -> récupération d'un nouveau token avec getToken
//        connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
//        connect(this, SIGNAL(signalTimerTimeout(QString,QString,QString)), this, SLOT(getToken(QString,QString,QString)));
    }


////////////////////    ATTRIBUTS   ////////////////////
    QString Api;
    QString clientId;
    QString clientSecretCode;
    QString refreshToken;
    QString accessToken;

    int maxResults = 3;

    QNetworkAccessManager manager;
    QNetworkReply *getTokenReply;
    QNetworkReply *checkTokenInfoReply;

    QTimer *timer = new QTimer();
    const int refreshTime = 3500000;

    QVector<QString> videoIdArray;
    QVector<QString> videoTitleArray;
    QVector<QString> videoThumbnailsUrlArray;

    QVector<QString> playlistNameArray;
    QVector<QString> playlistIdArray;

    QString requestSource;
    QString playlistName;
    QString playlistId;



////////////////////    METHODES    ////////////////////
    void processPlaylistsElements(const QByteArray &data);
    void processPlaylists(const QByteArray &data);
    void checkTokenInfo();

signals:
    void fetchPlaylistElementSignal();
    void fetchPlaylistsSignal();
    void signalTimerTimeout(QString,QString,QString);
    void videoDataLoaded(QVector<QString>,QVector<QString>,QVector<QString>,QString);
    void playlistListLoaded(QVector<QString>,QVector<QString>);


public slots:
    void fetchPlaylistElements();
    void fetchPlaylists();

    // void getToken(QString clientId,QString clientSecretCode,QString refreshToken);
    void getToken();

    void timerTimeout();

    void retrieveAccessToken();
    void retrieveAccessTokenInfo();
    void printToken();

    void updateRequestSource(QString newRequest);
    void updatePlaylistId(int index);

    void updateParams(QString,QString);


private:

};


#endif // YOUTUBEAPI_H
