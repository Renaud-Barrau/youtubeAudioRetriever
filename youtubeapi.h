/**
 * @file youtubeapi.h
 * @brief Header of the youtubeApi class
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

/** @class youtubeApi
 * @brief The youtubeApi class is responsible for interacting with the YouTube API.
 *
 * This file handle the login process with OAuth2.0 to retrieve personnal data on your youtube account.
 * You must create a project [here](https://console.cloud.google.com) in order to have your API key, client ID and client secret code.
 * Also, you will need a "Refresh token". A refresh token is a token created by google and linked to your account that allows you to generate an "acces token".
 * The only purpose of the refresh token is to generate acces token.
 * Refresh tokens are infinites, whereas access token are only valid for 1 hour.
 *
 * You only need to provide to this application a refresh token, as it will handle the generation of access token by itself.
 *
 * To obtain a refresh token, you can visit the [OAuth2.0 playground](https://developers.google.com/oauthplayground).
 * On the right side, you need to click on the configuration button and check "Use your own OAuth credentials", then input your data.
 *
 * Then on the left side, scroll down to the "YouTube Data API v3 v3" (version might change), unroll the menu and select which option you want.
 * For this application, you need at least the https://www.googleapis.com/auth/youtube option.
 * Then click on the "Authorize API's" and follow the process.
 * If everything went fine, you should be redirected to a page with a "exchange authorization code for tokens" button.
 * Finally, you should find your refresh token in the HTTP Json response section.
 * As far as I have experienced it, a refresh token should start with "1//".
 */
class youtubeApi : public QObject
{
    Q_OBJECT
public:
    explicit youtubeApi(QObject *parent = nullptr) : QObject(parent){
    }


    /**
     * @brief The API key for the YouTube API.
     */
    QString Api;

    /**
     * @brief The client ID for the OAuth 2.0 authentication process.
     */
    QString clientId;

    /**
     * @brief The client secret code for the OAuth 2.0 authentication process.
     */
    QString clientSecretCode;

    /**
     * @brief The refresh token for the OAuth 2.0 authentication process.
     */
    QString refreshToken;

    /**
     * @brief The access token for the YouTube API.
     */
    QString accessToken;

    /**
     * @brief The maximum number of results to be returned by the YouTube API in a single request.
     */
    int maxResults;

    /**
     * @brief The QNetworkAccessManager object used for making HTTP requests to the YouTube API.
     */
    QNetworkAccessManager manager;

    /**
     * @brief The QNetworkReply object for the GET token info request.
     */
    QNetworkReply *getTokenReply;

    /**
     * @brief The QNetworkReply object for the GET token info request.
     */
    QNetworkReply *checkTokenInfoReply;

    /**
     * @brief A vector of strings containing the video IDs.
     */
    QVector<QString> videoIdArray;

    /**
     * @brief A vector of strings containing the video titles.
     */
    QVector<QString> videoTitleArray;

    /**
     * @brief A vector of strings containing the video thumbnail URLs.
     */
    QVector<QString> videoThumbnailsUrlArray;

    /**
     * @brief A vector of strings containing the playlist names.
     */
    QVector<QString> playlistNameArray;

    /**
     * @brief A vector of strings containing the playlist IDs.
     */
    QVector<QString> playlistIdArray;

    /**
     * @brief A string indicating the source of the request.
     */
    QString requestSource;

    /**
     * @brief A string indicating a temporary playlist name.
     */
   QString playlistName;

    /**
     * @brief A string indicating a temporary playlist id.
     */
   QString playlistId;



    void processPlaylistsElements(const QByteArray &data);
    void processPlaylists(const QByteArray &data);
    void checkTokenInfo();
    void fetchPlaylistElements();
    void fetchPlaylists();
    void getToken();
    void retrieveAccessToken();
    void retrieveAccessTokenInfo();

signals:
    /**
     * @brief A signal emitted when playlist names and IDs are loaded.
     */
    void playlistListLoaded(QVector<QString> playlistNameArray,QVector<QString> playlistIdArray);
    /**
     * @brief A signal emitted when video names, IDs and thumbnails urls are loaded.
     */
    void videoDataLoaded(QVector<QString> videoTitleArray,QVector<QString> videoIdArray,QVector<QString> videoThumbnailsUrlArray,QString playlistName);

//    void updatePlaylistId(int index);

private:

};


#endif // YOUTUBEAPI_H
