#include "youtubeApi.h"
#include <iostream>
// #include <unistd.h>


void youtubeApi::fetchPlaylistElements()
{
    if(youtubeApi::playlistId == ""){
        cout << "fetch playlist first before downloading" << endl;
        return;
    }
    // QUrl url("https://www.googleapis.com/youtube/v3/playlists");
    QUrl url("https://www.googleapis.com/youtube/v3/playlistItems");
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("mine", "true");
    query.addQueryItem("playlistId", youtubeApi::playlistId);
    query.addQueryItem("key", youtubeApi::Api);
    query.addQueryItem("maxResults", QString::number(youtubeApi::maxResults));
    url.setQuery(query);

    //cout << url.toString().toStdString() << endl;

    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer ") + youtubeApi::accessToken.toUtf8());
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

void youtubeApi::fetchPlaylists(){
    // QUrl url("https://www.googleapis.com/youtube/v3/playlists");


    QUrl url("https://www.googleapis.com/youtube/v3/playlists");
    QUrlQuery query;
    query.addQueryItem("part", "snippet");
    query.addQueryItem("mine", "true");
//    query.addQueryItem("playlistId", "PLwuIM-4Ygcenwu4_GqfXZdtr_rvpULIjM");
    query.addQueryItem("key", youtubeApi::Api);
//    query.addQueryItem("maxResults", QString::number(maxResults));
    url.setQuery(query);

    //cout << url.toString().toStdString() << endl;

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
    emit playlistListLoaded(youtubeApi::playlistNameArray,youtubeApi::playlistIdArray);
}

// void youtubeApi::getToken(QString clientId,QString clientSecretCode,QString refreshToken)
void youtubeApi::getToken()
{
    QUrl url("https://oauth2.googleapis.com/token");
    QUrlQuery query;
    query.addQueryItem("grant_type", "refresh_token");
    query.addQueryItem("client_id", clientId);
    query.addQueryItem("client_secret", clientSecretCode);
    query.addQueryItem("refresh_token", refreshToken);

    // Ajouter les paramètres à l'URL de la requête
    url.setQuery(query);

    // Créer un objet QNetworkRequest pour la requête HTTPS
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Envoyer la requête HTTPS
    getTokenReply = manager.post(request, query.toString(QUrl::FullyEncoded).toUtf8());

    // Connecter le signal finished() du QNetworkReply à un slot pour traiter la réponse

    connect(getTokenReply, &QNetworkReply::finished, this, &youtubeApi::retrieveAccessToken);

//    reply->deleteLater();

}

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

void youtubeApi::retrieveAccessToken(){
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
        youtubeApi::accessToken = access_token;

//        cout << "youtubeApi::accessToken : " << youtubeApi::accessToken.toStdString() << endl;
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

void youtubeApi::retrieveAccessTokenInfo(){
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

void youtubeApi::printToken(){
    cout << "mon token : " << youtubeApi::accessToken.toStdString() << endl;
}

void youtubeApi::timerTimeout(){
    emit signalTimerTimeout(youtubeApi::clientId,youtubeApi::clientSecretCode,youtubeApi::refreshToken);
}

void youtubeApi::updateRequestSource(QString newRequest){
    youtubeApi::requestSource = newRequest;
}

void youtubeApi::updatePlaylistId(int index){
    youtubeApi::playlistId = youtubeApi::playlistIdArray.at(index);
    youtubeApi::playlistName = youtubeApi::playlistNameArray.at(index);
}

void youtubeApi::updateParams(QString key, QString value){
    if(key == "apiKey"){
        youtubeApi::Api = value;
    }
    else if(key == "clientId"){
        youtubeApi::clientId = value;
    }
    else if(key == "clientSecretCode"){
        youtubeApi::clientSecretCode = value;
    }
    else if(key == "refreshToken"){
        youtubeApi::refreshToken = value;
    }
    else if(key == "videoNumber"){
        youtubeApi::maxResults = value.toInt();
    }
    else{
    }
}
