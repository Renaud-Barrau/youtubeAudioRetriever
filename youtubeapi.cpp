#include "youtubeapi.h"
#include <iostream>
// #include <unistd.h>


void YouTubeAPI::fetchPlaylistElements()
{
    if(YouTubeAPI::playlistId == ""){
        cout << "fetch playlist first before downloading" << endl;
        return;
    }
    // QUrl url("https://www.googleapis.com/youtube/v3/playlists");
    QUrl url("https://www.googleapis.com/youtube/v3/playlistItems");
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("mine", "true");
    query.addQueryItem("playlistId", YouTubeAPI::playlistId);
    query.addQueryItem("key", YouTubeAPI::Api);
    query.addQueryItem("maxResults", QString::number(YouTubeAPI::maxResults));
    url.setQuery(query);

    //cout << url.toString().toStdString() << endl;

    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + YouTubeAPI::accessToken.toUtf8());
    request.setRawHeader(QByteArray("Accept"), QByteArray("application/json"));
//    int i = 0;
//    while(i < request.rawHeaderList().length()){
//        cout << "Raw Header " << i << " : " << request.rawHeaderList()[i].toStdString() << endl;
//        i++;
//    }

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

void YouTubeAPI::processPlaylistsElements(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();
    QJsonArray items = rootObj.value("items").toArray();

    cout << "Playlists:" << endl;
    YouTubeAPI::videoTitleArray.clear();
    YouTubeAPI::videoIdArray.clear();
    YouTubeAPI::videoThumbnailsUrlArray.clear();

    foreach (const QJsonValue &value, items) {
        QJsonObject playlist = value.toObject();
        QString title = playlist.value("snippet").toObject().value("title").toString();
//        QString id = playlist.value("id").toString();
        QString videoId = playlist.value("snippet").toObject().value("resourceId").toObject().value("videoId").toString();
        QString videoThumbnailUrl = playlist.value("snippet").toObject().value("thumbnails").toObject().value("maxres").toObject().value("url").toString();
//        int index = playlist.value("snippet").toObject().value("position").toInt();
        cout << "Title: " << title.toStdString() << " | videoId : " << videoId.toStdString() << " | thumbnail URL : " << videoThumbnailUrl.toStdString() << endl;
        YouTubeAPI::videoTitleArray.append(title);
        YouTubeAPI::videoIdArray.append(videoId);
        YouTubeAPI::videoThumbnailsUrlArray.append(videoThumbnailUrl);

    }
    emit videoDataLoaded(YouTubeAPI::videoTitleArray,YouTubeAPI::videoIdArray,YouTubeAPI::videoThumbnailsUrlArray,YouTubeAPI::playlistName);
}

void YouTubeAPI::fetchPlaylists(){
    // QUrl url("https://www.googleapis.com/youtube/v3/playlists");


    QUrl url("https://www.googleapis.com/youtube/v3/playlists");
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("mine", "true");
//    query.addQueryItem("playlistId", "PLwuIM-4Ygcenwu4_GqfXZdtr_rvpULIjM");
    query.addQueryItem("key", YouTubeAPI::Api);
//    query.addQueryItem("maxResults", QString::number(maxResults));
    url.setQuery(query);

    //cout << url.toString().toStdString() << endl;

    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + YouTubeAPI::accessToken.toUtf8());
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

void YouTubeAPI::processPlaylists(const QByteArray &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject rootObj = doc.object();
    QJsonArray items = rootObj.value("items").toArray();

    cout << "Playlists:" << endl;
    foreach (const QJsonValue &value, items) {
        QJsonObject playlist = value.toObject();
        QString playlistTitle = playlist.value("snippet").toObject().value("title").toString();
        QString playlistId = playlist.value("id").toString();

        if(!YouTubeAPI::playlistNameArray.contains(playlistTitle)){
            YouTubeAPI::playlistNameArray.append(playlistTitle);
            YouTubeAPI::playlistIdArray.append(playlistId);
        }



        cout << "Playlist Title: " << playlistTitle.toStdString() << " | Playlist Id : " << playlistId.toStdString() << endl;

    }
    emit playlistListLoaded(YouTubeAPI::playlistNameArray,YouTubeAPI::playlistIdArray);
}

// void YouTubeAPI::getToken(QString clientId,QString clientSecretCode,QString refreshToken)
void YouTubeAPI::getToken()
{
    QUrl url("https://oauth2.googleapis.com/token");
    QUrlQuery query;
    query.addQueryItem("grant_type", "refresh_token");
    query.addQueryItem("client_id", YouTubeAPI::clientId);
    query.addQueryItem("client_secret", YouTubeAPI::clientSecretCode);
    query.addQueryItem("refresh_token", YouTubeAPI::refreshToken);

    // Ajouter les paramètres à l'URL de la requête
    url.setQuery(query);

    // Créer un objet QNetworkRequest pour la requête HTTPS
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Envoyer la requête HTTPS
    getTokenReply = manager.post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    // Connecter le signal finished() du QNetworkReply à un slot pour traiter la réponse

    connect(getTokenReply, &QNetworkReply::finished, this, &YouTubeAPI::retrieveAccessToken);

//    reply->deleteLater();

}

void YouTubeAPI::checkTokenInfo(){
    if(YouTubeAPI::accessToken == ""){
        cout << "Token string is empty" << endl;
        return;
    }
    else{
        cout << "grabing token info" << endl;
        cout << "Token is : " << YouTubeAPI::accessToken.toStdString() << endl;
        QUrl url("https://oauth2.googleapis.com/tokeninfo");
        url.setQuery(QUrlQuery("access_token=" + YouTubeAPI::accessToken));
        QNetworkRequest request(url);
        checkTokenInfoReply = manager.get(request);
        connect(checkTokenInfoReply, &QNetworkReply::finished, this, &YouTubeAPI::retrieveAccessTokenInfo);
    }
}

void YouTubeAPI::retrieveAccessToken(){
    if (getTokenReply->error() == QNetworkReply::NoError) {
        // Extraire l'accès_token de la réponse
        QByteArray responseData = getTokenReply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        QString access_token = jsonObject["access_token"].toString();
        QString token_type = jsonObject["token_type"].toString();
        int expires_in = jsonObject["expires_in"].toInt();
        std::cout << "Access token:" << access_token.toStdString() << std::endl;
        std::cout << "token_type:" << token_type.toStdString() << std::endl;
        std::cout << "expires_in:" << expires_in << std::endl;
        YouTubeAPI::accessToken = access_token;

//        cout << "YoutubeAPI::accessToken : " << YouTubeAPI::accessToken.toStdString() << endl;
    }
    else {
        cout << "Error:" << getTokenReply->errorString().toStdString() << endl;

    }if(YouTubeAPI::requestSource == "fetchPlaylistElements"){
        emit fetchPlaylistElementSignal();
    }
    else if (YouTubeAPI::requestSource == "fetchPlaylists"){
        emit fetchPlaylistsSignal();
    }
    else{
        cout << "no suitable request declarator" << endl;
    }


}

void YouTubeAPI::retrieveAccessTokenInfo(){
    if (checkTokenInfoReply->error() == QNetworkReply::NoError) {
        // Lire les données de la réponse et les analyser en tant que document JSON
        QByteArray responseData = checkTokenInfoReply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonResponse.object();
        QString scope = jsonObject["scope"].toString();
        QString expires_in = jsonObject["expires_in"].toString();
        cout << "scope: " << scope.toStdString() << endl;
        cout << "expires_in: " << expires_in.toStdString() << endl;
    }
}

void YouTubeAPI::printToken(){
    cout << "mon token : " << YouTubeAPI::accessToken.toStdString() << endl;
}

void YouTubeAPI::timerTimeout(){
    emit signalTimerTimeout(YouTubeAPI::clientId,YouTubeAPI::clientSecretCode,YouTubeAPI::refreshToken);
}

void YouTubeAPI::updateRequestSource(QString newRequest){
    YouTubeAPI::requestSource = newRequest;
}

void YouTubeAPI::updatePlaylistId(int index){
    YouTubeAPI::playlistId = YouTubeAPI::playlistIdArray.at(index);
    YouTubeAPI::playlistName = YouTubeAPI::playlistNameArray.at(index);
}

void YouTubeAPI::updateParams(QString key, QString value){
    if(key == "apiKey"){
        YouTubeAPI::Api = value;
    }
    else if(key == "clientId"){
        YouTubeAPI::clientId = value;
    }
    else if(key == "clientSecretCode"){
        YouTubeAPI::clientSecretCode = value;
    }
    else if(key == "refreshToken"){
        YouTubeAPI::refreshToken = value;
    }
    else if(key == "videoNumber"){
        YouTubeAPI::maxResults = value.toInt();
    }
    else{
    }
}
