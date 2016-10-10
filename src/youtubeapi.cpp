/***************************************************************************
 *   Copyright (C) 2016 by Ricardo Gonçalves                               *
 *   ricardompgoncalves@gmail.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include <QUrl>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "youtubeapi.h"

#include <iostream>
#include <typeinfo>

YoutubeAPI::YoutubeAPI(QObject *parent) : QObject(parent)
{

}

void YoutubeAPI::runRequest(const char *url, QUrlQuery &urlQuery, void (YoutubeAPI::*method)(QNetworkReply *))
{
    QUrl urlBuilder(url);

    // Add Google API Key
    urlQuery.addQueryItem("key", "AIzaSyCgcVV60swEYVzLYI74l-UH0CAEPyvm-0E");    // TODO: Warning - Private KEY

    // Add the query string to the URL
    urlBuilder.setQuery(urlQuery);

    // Request and specific headers
    QNetworkRequest request;
    request.setUrl(urlBuilder);
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

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    this->connect(networkManager, &QNetworkAccessManager::finished, this, method);
    networkManager->get(request);       // GET method
}

void YoutubeAPI::searchList(QString queryTerm)
{
    // Query string
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("part", "snippet");
    urlQuery.addQueryItem("type", "video");     // TODO: Playlist support
    urlQuery.addQueryItem("maxResults", "50");
    urlQuery.addQueryItem("q", queryTerm.replace(' ','+'));     // Search string, URL encoded

    // Run the request
    this->runRequest(YOUTUBE_API_SEARCH, urlQuery, &YoutubeAPI::replySearchList);
}

void YoutubeAPI::searchRelated(QString id)
{
    // Query string
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("part", "snippet");
    urlQuery.addQueryItem("type", "video");
    urlQuery.addQueryItem("maxResults", "15");
    urlQuery.addQueryItem("relatedToVideoId", id);

    // Run the request
    this->runRequest(YOUTUBE_API_SEARCH, urlQuery, &YoutubeAPI::replySearchList);

}

void YoutubeAPI::videosList(QString id)
{
    // Query string
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("part", "snippet");
    urlQuery.addQueryItem("id", id);

    // Run the request
    this->runRequest(YOUTUBE_API_VIDEOS, urlQuery, &YoutubeAPI::replyVideosList);
}

void YoutubeAPI::replySearchList(QNetworkReply *reply)
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
}

void YoutubeAPI::replyVideosList(QNetworkReply *reply)
{
    // Reads the reply
    QByteArray response = reply->readAll();

    // Prints result
    //std::cout << QString(response).toStdString() << std::endl << std::endl;

    QJsonParseError e;
    QJsonObject result = QJsonDocument::fromJson(response, &e).object();

    // Get list of results
    QJsonArray items = result.value("items").toArray();

    // Iterate over result items
    foreach (QVariant item, items) {
        QMap<QString, QVariant> map = item.toMap();
        QMap<QString, QVariant> snippet = item.toMap()["snippet"].toMap();

        QString id = map["id"].toMap()["videoId"].toString();
        QString title = snippet["title"].toString();
        QString description = snippet["description"].toString();
        QString channel = snippet["channelTitle"].toString();
        QString thumbnail = snippet["thumbnails"].toMap()["high"].toMap()["url"].toString();

        // Emits a signal with results
        emit resultsVideosListAvailable(title);
    }
}

YoutubeAPI::~YoutubeAPI()
{

}
