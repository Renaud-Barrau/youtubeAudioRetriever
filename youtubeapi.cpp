/**
 * @file youtubeapi.cpp
 * @brief Implementation of the youtubeApi class

 */


#include "youtubeApi.h"
#include <iostream>

/** @fn youtubeApi::getToken()
 * @brief This method sends a request to the Google OAuth 2.0 server to obtain an access token.
 *
 * The method constructs a URL for the token endpoint of the Google OAuth 2.0 server, and adds the necessary query parameters for a refresh token grant. The query parameters include the grant type, client ID, client secret, and refresh token.
 *
 * The method then sets the query string for the URL, and creates a network request object for the URL. It sets the content type header of the request to "application/x-www-form-urlencoded".
 *
 * Finally, the method sends the request using the QNetworkAccessManager object, and connects the finished() signal of the reply object to the retrieveAccessToken() slot of the youtubeApi object.
 *
 * @param None
 * @return None
 */
void youtubeApi::getToken()
{
    QUrl url("https://oauth2.googleapis.com/token");
    QUrlQuery query;
    query.addQueryItem("grant_type", "refresh_token");
    query.addQueryItem("client_id", clientId);
    query.addQueryItem("client_secret", clientSecretCode);
    query.addQueryItem("refresh_token", refreshToken);

    url.setQuery(query);


    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    getTokenReply = manager.post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    connect(getTokenReply, &QNetworkReply::finished, this, &youtubeApi::retrieveAccessToken);


}

/** @fn youtubeApi::retrieveAccessToken()
 * @brief This method retrieves the access token from the response of the Google OAuth 2.0 server.
 *
 * The method is called when the finished() signal of the reply object is emitted. It first checks if the reply object has no error. If there is an error, it prints the error string to the console.
 *
 * If there is no error, the method reads the entire response data from the reply object, and converts it to a QJsonDocument object. It then extracts the access token, token type, and expiration time from the JSON object, and prints them to the console.
 *
 * Finally, the method sets the accessToken member variable of the youtubeApi object to the retrieved access token.
 *
 * Depending of the state of the youtubeApi::requestSource variable, fetchPlaylistElements() or fetchPlaylists() are called.
 * @param None
 * @return None
 */
void youtubeApi::retrieveAccessToken(){
    if (getTokenReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = getTokenReply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        QString access_token = jsonObject["access_token"].toString();
        QString token_type = jsonObject["token_type"].toString();
        int expires_in = jsonObject["expires_in"].toInt();
        std::cout << "Access token:" << access_token.toStdString() << std::endl;
        std::cout << "token_type:" << token_type.toStdString() << std::endl;
        std::cout << "expires_in:" << expires_in << std::endl;
        youtubeApi::accessToken = access_token;
    }
    else {
        cout << "Error:" << getTokenReply->errorString().toStdString() << endl;

    }if(youtubeApi::requestSource == "fetchPlaylistElements"){
        //        emit fetchPlaylistElementSignal();
        youtubeApi::fetchPlaylistElements();
    }
    else if (youtubeApi::requestSource == "fetchPlaylists"){
        //        emit fetchPlaylistsSignal();
        youtubeApi::fetchPlaylists();
    }
    else{
        cout << "no suitable request declarator" << endl;
    }
}






/** @fn youtubeApi::fetchPlaylists()
 * @brief Fetches the playlists of the authenticated user from the YouTube API.
 *
 * This method sends a GET request to the YouTube API's playlists endpoint with the
 * appropriate query parameters and headers. When the request is finished, it checks
 * for errors and, if there are none, calls the processPlaylists() method to parse the
 * JSON response and extract the playlist data.
 *
 */
void youtubeApi::fetchPlaylists(){
    QUrl url("https://www.googleapis.com/youtube/v3/playlists");
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("mine", "true");
    query.addQueryItem("key", youtubeApi::Api);
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + youtubeApi::accessToken.toUtf8());
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));

    QNetworkReply *reply = manager.get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            processPlaylists(responseData);
        } else {
            cout << "Error: " << reply->errorString().toStdString() << endl;
        }
        reply->deleteLater();
    });
}

/** @fn youtubeApi::processPlaylists(const QByteArray &data)
 * @brief Processes the JSON data containing the user's playlists and extracts their titles and IDs.
 *
 * This method is called when the fetchPlaylists() method has successfully retrieved the JSON data containing the user's playlists.
 * It takes the JSON data as a QByteArray and parses it using the QJsonDocument and QJsonObject classes.
 * It then iterates over the "items" array in the JSON data, which contains the individual playlist objects.
 * For each playlist, it extracts the title and ID and adds them to the youtubeApi::playlistNameArray and youtubeApi::playlistIdArray member variables, respectively, if the title is not already in the array.
 * It also prints the playlist title and ID to the console.
 *
 * @param data The JSON data containing the user's playlists, as a QByteArray.
 */
void youtubeApi::processPlaylists(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();
    QJsonArray items = rootObj.value("items").toArray();

    cout << "Playlists:" << endl;
    foreach (const QJsonValue &value, items) {
        QJsonObject playlist = value.toObject();
        QString playlistTitle = playlist.value("snippet").toObject().value("title").toString();
        QString playlistId = playlist.value("id").toString();

        if(!youtubeApi::playlistNameArray.contains(playlistTitle)){
            youtubeApi::playlistNameArray.append(playlistTitle);
            youtubeApi::playlistIdArray.append(playlistId);
        }

        cout << "Playlist Title: " << playlistTitle.toStdString() << " | Playlist Id : " << playlistId.toStdString() << endl;

    }
    // emit playlistListLoaded(youtubeApi::playlistNameArray,youtubeApi::playlistIdArray);
}


/** @fn youtubeApi::fetchPlaylistElements()
 * @brief Fetches the elements of a playlist from the YouTube API.
 *
 * This method first checks if the youtubeApi::playlistId is empty. If it is, the method prints an error message and returns.
 * Otherwise, the method constructs a URL for the YouTube API's `playlistItems` endpoint, with the following query parameters:
 * - `part`: set to `snippet`, to retrieve the basic metadata of the playlist items.
 * - `mine`: set to `true`, to retrieve only the playlist items that belong to the authenticated user.
 * - `playlistId`: set to the ID of the playlist to retrieve : youtubeApi::playlistId.
 * - `key`: set to the API key of the application : youtubeApi::Api.
 * - `maxResults`: set to the maximum number of playlist items to retrieve in a single request : youtubeApi::maxResults.
 *
 * The method then sets the `Authorization` and `Accept` headers of the request, and sends a GET request to the constructed URL.
 * When the request is finished, the method checks if there was an error. If there was, the method prints an error message and returns.
 * Otherwise, the method calls the processPlaylistsElements() method to process the JSON response.
 *
 *
 */
void youtubeApi::fetchPlaylistElements()
{
    if(youtubeApi::playlistId == ""){
        cout << "fetch playlist first before downloading" << endl;
        return;
    }
    QUrl url("https://www.googleapis.com/youtube/v3/playlistItems");
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("mine", "true");
    query.addQueryItem("playlistId", youtubeApi::playlistId);
    query.addQueryItem("key", youtubeApi::Api);
    query.addQueryItem("maxResults", QString::number(youtubeApi::maxResults));
    url.setQuery(query);


    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + youtubeApi::accessToken.toUtf8());
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));

    QNetworkReply *reply = manager.get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            processPlaylistsElements(responseData);
        } else {
            cout << "Error: " << reply->errorString().toStdString() << endl;
        }
        reply->deleteLater();
    });
}

/** @fn youtubeApi::processPlaylistsElements(const QByteArray &data)
 * @brief Processes the JSON data containing the elements of a YouTube playlist.
 *
 * This method is called when the fetchPlaylistElements() method has successfully retrieved the JSON data containing the elements of a YouTube playlist.
 * It takes the JSON data as a QByteArray and processes it to extract the title, video ID, and thumbnail URL of each video in the playlist.
 * The extracted information is then stored in the youtubeApi::videoTitleArray, youtubeApi::videoIdArray, and youtubeApi::videoThumbnailsUrlArray member variables of the youtubeApi class, respectively.
 *
 * @param data The JSON data containing the elements of a YouTube playlist, as a QByteArray.
 */
void youtubeApi::processPlaylistsElements(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();
    QJsonArray items = rootObj.value("items").toArray();

    cout << "Playlists:" << endl;
    youtubeApi::videoTitleArray.clear();
    youtubeApi::videoIdArray.clear();
    youtubeApi::videoThumbnailsUrlArray.clear();

    foreach (const QJsonValue &value, items) {
        QJsonObject playlist = value.toObject();
        QString title = playlist.value("snippet").toObject().value("title").toString();
        QString videoId = playlist.value("snippet").toObject().value("resourceId").toObject().value("videoId").toString();
        QString videoThumbnailUrl = playlist.value("snippet").toObject().value("thumbnails").toObject().value("maxres").toObject().value("url").toString();
        cout << "Title: " << title.toStdString() << " | videoId : " << videoId.toStdString() << " | thumbnail URL : " << videoThumbnailUrl.toStdString() << endl;
        youtubeApi::videoTitleArray.append(title);
        youtubeApi::videoIdArray.append(videoId);
        youtubeApi::videoThumbnailsUrlArray.append(videoThumbnailUrl);

    }
//    emit videoDataLoaded(youtubeApi::videoTitleArray,youtubeApi::videoIdArray,youtubeApi::videoThumbnailsUrlArray,youtubeApi::playlistName);
}






/** @fn youtubeApi::checkTokenInfo()
 * @brief Checks the validity of the current access token.
 *
 * This method first checks if the access token is empty. If it is, the method prints an error message and returns.
 * Otherwise, the method sends a GET request to the Google OAuth 2.0 token info endpoint to retrieve information about the token.
 * The endpoint URL is "https://oauth2.googleapis.com/tokeninfo", and the query parameter is the current access token.
 * The method then connects the finished() signal of the QNetworkReply object to the retrieveAccessTokenInfo() slot.
 *
 * @note This method was a test method used during development, and is not used in the application.
 */
void youtubeApi::checkTokenInfo(){
    if(youtubeApi::accessToken == ""){
        cout << "Token string is empty" << endl;
        return;
    }
    else{
        cout << "grabing token info" << endl;
        cout << "Token is : " << youtubeApi::accessToken.toStdString() << endl;
        QUrl url("https://oauth2.googleapis.com/tokeninfo");
        url.setQuery(QUrlQuery("access_token=" + youtubeApi::accessToken));
        QNetworkRequest request(url);
        checkTokenInfoReply = manager.get(request);
        connect(checkTokenInfoReply, &QNetworkReply::finished, this, &youtubeApi::retrieveAccessTokenInfo);
    }
}


/** @fn youtubeApi::retrieveAccessTokenInfo()
 * @brief Retrieves the access token information from the Google OAuth 2.0 API.
 *
 * This method is called when the QNetworkReply object, checkTokenInfoReply, emits the finished() signal. It checks if the reply has no error and if so, it reads the response data and parses it as a JSON object. It then retrieves the scope and expires\_in fields from the JSON object and prints them to the console.
 *
 * @note This method was a test method used during development, and is not used in the application.
 */
void youtubeApi::retrieveAccessTokenInfo(){
    if (checkTokenInfoReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = checkTokenInfoReply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        QString scope = jsonObject["scope"].toString();
        QString expires_in = jsonObject["expires_in"].toString();
        cout << "scope: " << scope.toStdString() << endl;
        cout << "expires_in: " << expires_in.toStdString() << endl;
    }
}






//void youtubeApi::updatePlaylistId(int index){
//    youtubeApi::playlistId = youtubeApi::playlistIdArray.at(index);
//    youtubeApi::playlistName = youtubeApi::playlistNameArray.at(index);
//}

