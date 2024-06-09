/**
 * @file youtubeapi.h
 * @brief This file handle the login process with OAuth2.0 to retrieve personnal data on your youtube account.
 * You must create a project [here](https://console.cloud.google.com) in order to have your API key, client ID and client secret code.
 * Also, you will need a "Refresh token". A refresh token is a token created by google and linked yo your account that allows you to generate an "acces token".
 * The only purpose of the refresh token is to generate acces token.
 * Refresh tokens are infinites, whereas access token are only valid for 1 hour.
 *
 * You only need to provide to this application a refresh token, as it will handle the generation of access token by itself.
 *
 * To obtains a refresh token, you can visit the [OAuth2.0 playground](https://developers.google.com/oauthplayground).
 * On the right side, you need to click on the configuration button and check "Use your own OAuth credentials", then input your data.
 *
 * Then on the left side, scroll down to the "YouTube Data API v3 v3" (version might change), unroll the menu and select which option you want.
 * For this application, you need at least the https://www.googleapis.com/auth/youtube option.
 * Then click on the "Authorize API's" and follow the process.
 * If everything went fine, you should be redirected to a page with a "exchange authorization code for tokens" button.
 * Finally, you should find your refresh token in the HTTP Json response section.
 * As far as I have experienced it, a refresh token should start with "1//".
 *
 *
 *
 *
 */



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

        timer->setInterval(refreshTime);
        timer->start();

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

// signals:
//     void fetchPlaylistElementSignal();
//     void fetchPlaylistsSignal();
//     void signalTimerTimeout(QString,QString,QString);
//     void videoDataLoaded(QVector<QString>,QVector<QString>,QVector<QString>,QString);
//     void playlistListLoaded(QVector<QString>,QVector<QString>);


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
