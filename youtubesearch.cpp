#include <QUrl>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>

#include "youtubesearch.h"

#include <iostream>


YoutubeSearch::YoutubeSearch(QObject *parent) : QObject(parent)
{

}

void YoutubeSearch::search(QString search)
{
    QUrlQuery urlQuery;

    // Base URL
    QUrl url("https://content.googleapis.com/youtube/v3/search");
    urlQuery.addQueryItem("part", "snippet");
    //urlQuery.addQueryItem("key", "AIzaSyCFj15TpkchL4OUhLD1Q2zgxQnMb7v3XaM");  // Google KEY
    urlQuery.addQueryItem("key", "AIzaSyCgcVV60swEYVzLYI74l-UH0CAEPyvm-0E");    // Warning: Private KEY
    urlQuery.addQueryItem("type", "playlist,video");
    urlQuery.addQueryItem("maxResults", "50");

    // Search String
    QString searchQuery = search.replace(' ','+');

    // Add query parameter to the URL
    urlQuery.addQueryItem("q", searchQuery);
    url.setQuery(urlQuery);

    // Request and specific headers
    QNetworkRequest request;
    request.setUrl(url);
    //request.setRawHeader("Host", "content.googleapis.com");
    //request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0");
    //request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    //request.setRawHeader("Accept-Language", "en-US,en;q=0.5");
    //request.setRawHeader("Accept-Encoding", "gzip, deflate");
    //request.setRawHeader("X-JavaScript-User-Agent", "google-api-javascript-client/1.1.0-beta");
    //request.setRawHeader("X-ClientDetails", "appVersion=5.0%20(X11)&platform=Linux%20x86_64&userAgent=Mozilla%2F5.0%20(X11%3B%20Linux%20x86_64%3B%20rv%3A35.0)%20Gecko%2F20100101%20Firefox%2F35.0");
    request.setRawHeader("X-Origin", "https://developers.google.com");
    //request.setRawHeader("X-Referer", "https://developers.google.com");
    //request.setRawHeader("X-Goog-Encode-Response-If-Executable", "base64");
    //request.setRawHeader("Referer", "https://content.googleapis.com/static/proxy.html?jsh=m%3B%2F_%2Fscs%2Fapps-static%2F_%2Fjs%2Fk%3Doz.gapi.pt_PT.2H_NS8R3WEM.O%2Fm%3D__features__%2Fam%3DAQ%2Frt%3Dj%2Fd%3D1%2Ft%3Dzcms%2Frs%3DAGLTcCP16vYF78SM-2BOkCOIg42VdVq7YQ");
    //request.setRawHeader("Connection", "keep-alive");
    //request.setRawHeader("If-None-Match", "\"F9iA7pnxqNgrkOutjQAa9F2k8HY/H_EGcd-W0Fs1wftFDb5-3dmNY0Q\"");

    this->networkManager = new QNetworkAccessManager();
    this->connect(this->networkManager, &QNetworkAccessManager::finished, this, &YoutubeSearch::reply);
    this->networkManager->get(request);  // GET
}

void YoutubeSearch::reply(QNetworkReply *reply)
{
    // Reads the reply
    QByteArray response = reply->readAll();

    // Prints result
    //std::cout << QString(response).toStdString() << std::endl << std::endl;

    // create a json Parser
    //QJson::Parser parser;
    //QMap<QString, QVariant> result = parser.parse(reply).toMap();
    QJsonParseError e;
    QJsonObject result = QJsonDocument::fromJson(response, &e).object();

    // Emits a signal with results
    emit resultsAvailable(&result);

    // Destroys the object
    this->~YoutubeSearch();
}

YoutubeSearch::~YoutubeSearch()
{
    //this->networkManager->~QNetworkAccessManager();
}
