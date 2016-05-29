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

#include <iostream>

#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <qmmp/fileinfo.h>

#include "youtubevideostreams.h"


YoutubeVideoStreams::YoutubeVideoStreams(QObject *parent) : QObject(parent)
{

}

void YoutubeVideoStreams::fetchStreams(QString videoId)
{
    this->videoId = videoId;

    // Base URL
    QUrl url("https://www.youtube.com/watch");
    QUrlQuery urlQuery;

    // Add video parameter to the URL
    urlQuery.addQueryItem("v",videoId);
    url.setQuery(urlQuery);

    // Request and specific headers
    QNetworkRequest request;
    request.setUrl(url);
    //request.setRawHeader("Host", "www.youtube.com");
    //request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0");
    //request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    //request.setRawHeader("Accept-Language", "en-US,en;q=0.5");
    //request.setRawHeader("Accept-Encoding", "gzip, deflate");
    //request.setRawHeader("Cookie", "YSC=XpSfDGuUadY; VISITOR_INFO1_LIVE=ad4l-CZxLLM; PREF=f1=50000000&f5=30; GEUP=b9ae0844ae529881f8545ed7c9d904f9aQcAAAA=; ACTIVITY=1422551889138");
    //request.setRawHeader("Connection", "keep-alive");

    this->networkManager = new QNetworkAccessManager();
    connect(this->networkManager, &QNetworkAccessManager::finished, this, &YoutubeVideoStreams::reply);
    this->networkManager->get(request);  // GET
}


void YoutubeVideoStreams::reply(QNetworkReply *reply)
{
    // Reads the reply
    QString response = QString(reply->readAll());

    // Extracts adaptative_fmts from the reply
    int adaptative_fmts_start = response.indexOf("\"adaptive_fmts\"") + 17;	// strlen( "adaptive_fmts":" ) = 17
    QString adaptative_fmts = response.mid(
        adaptative_fmts_start,
        response.indexOf('"', adaptative_fmts_start) - adaptative_fmts_start);

    // Extracts url_encoded_fmt_stream_map from the reply
    int url_encoded_fmt_stream_map_start = response.indexOf("\"url_encoded_fmt_stream_map\"") + 30;	// strlen( "url_encoded_fmt_stream_map":" ) = 30
    QString url_encoded_fmt_stream_map = response.mid(
        url_encoded_fmt_stream_map_start,
        response.indexOf('"', url_encoded_fmt_stream_map_start) - url_encoded_fmt_stream_map_start);

// 	std::cout << "-- adaptative_fmts" << std::endl;
// 	std::cout << adaptative_fmts.toStdString() << std::endl << std::endl;
// 	std::cout << "-- url_encoded_fmt_stream_map" << std::endl;
// 	std::cout << url_encoded_fmt_stream_map.toStdString() << std::endl;
// 	std::cout << std::endl << std::endl << std::endl << std::endl;
// 	std::cout << reply.toStdString();

    // Process URL's and determines bestURL
    this->audioHighStream = -1;
    this->audioLowStream = -1;
    this->videoHighStream = -1;
    this->videoLowStream = -1;

    this->processStream(adaptative_fmts);
    this->processStream(url_encoded_fmt_stream_map);

    std::cout << "Audio streams: " << this->streamsAudio.size() << std::endl;
    std::cout << "Video streams: " << this->streamsVideo.size() << std::endl;

    // Emits a signal
    emit streamsAvailable(this);

    // Destroys the object
    this->~YoutubeVideoStreams();
}

void YoutubeVideoStreams::processStream(QString data)
{
    QStringList streams = data.split(",");
    foreach(QString stream, streams) {
        int ranking = 1;
        QString type;
        QString url;

        bool isAudio = false;

        QStringList params = stream.split("\\u0026");
        foreach(QString param, params) {
            //std::cout << param.toStdString() << std::endl;

            param = QUrl::fromPercentEncoding(param.toLatin1());
            param = param.replace('+',' ');

            //std::cout << param.toStdString() << std::endl;

            if(param.startsWith("url="))
                url = param.mid(4);	// Removes "url="
            else if(param.startsWith("type=")) {
                type = param.mid(5);
                if(type.startsWith("audio"))
                    ranking += 10000000, isAudio = true;
                if(type.startsWith("audio/mp4"))
                    ranking += 10000000;
            }
            else if(param.startsWith("bitrate="))
                ranking += param.mid(8).toInt();
            else if(param.startsWith("quality=")) {
                QString value = param.mid(8);
                if(value == "small")
                    ranking += 200000;
                if(value == "medium")
                    ranking += 600000;
                if(value == "high")
                    ranking += 1000000;
            }
        }
        //std::cout << "Ranking: " << ranking << std::endl;

        Stream streamObj(ranking, type, url);

        if(isAudio) {   // Audio
            int lastIndex = this->streamsAudio.size();
            this->streamsAudio.append(streamObj);   // Add audio stream

            // Audio High Stream
            if(this->audioHighStream < 0)
                this->audioHighStream = lastIndex;
            else {
                Stream audioHighStream = this->streamsAudio.at(this->audioHighStream);
                if(ranking > audioHighStream.getRanking())
                    this->audioHighStream = lastIndex;
            }

            // Audio Low Stream
            if(this->audioLowStream < 0)
                this->audioLowStream = lastIndex;
            else {
                Stream audioLowStream = this->streamsAudio.at(this->audioLowStream);
                if(ranking < audioLowStream.getRanking())
                    this->audioLowStream = lastIndex;
            }
        }
        else {      // Video
            int lastIndex = this->streamsVideo.size();
            this->streamsVideo.append(streamObj);      // Add video stream

            // Video High Stream
            if(this->videoHighStream < 0)
                this->videoHighStream = lastIndex;
            else {
                Stream videoHighStream = this->streamsVideo.at(this->videoHighStream);
                if(ranking > videoHighStream.getRanking())
                    this->videoHighStream = lastIndex;
            }

            // Video Low Stream
            if(this->videoLowStream < 0)
                this->videoLowStream = lastIndex;
            else {
                Stream videoLowStream = this->streamsVideo.at(this->videoLowStream);
                if(ranking < videoLowStream.getRanking())
                    this->videoLowStream = lastIndex;
            }
        }
    }
}

YoutubeVideoStreams::~YoutubeVideoStreams()
{
    //this->networkManager->~QNetworkAccessManager();
}

/* ***************
 * Getters
 * **************/

QString YoutubeVideoStreams::getVideoId()
{
    return this->videoId;
}

QList<YoutubeVideoStreams::Stream> YoutubeVideoStreams::getStreams()
{
    return this->streamsVideo + this->streamsAudio;
}

YoutubeVideoStreams::Stream YoutubeVideoStreams::getStreamAudioHigh()
{
    return this->streamsAudio.at(this->audioHighStream);
}

YoutubeVideoStreams::Stream YoutubeVideoStreams::getStreamAudioMedium()
{
    // TODO
    return this->streamsAudio.at(0);
}

YoutubeVideoStreams::Stream YoutubeVideoStreams::getStreamAudioLow()
{
    return this->streamsAudio.at(this->audioLowStream);
}

YoutubeVideoStreams::Stream YoutubeVideoStreams::getStreamVideoHigh()
{
    return this->streamsVideo.at(this->videoHighStream);
}

YoutubeVideoStreams::Stream YoutubeVideoStreams::getStreamVideoMedium()
{
    // TODO
    return this->streamsVideo.at(0);
}

YoutubeVideoStreams::Stream YoutubeVideoStreams::getStreamVideoLow()
{
    return this->streamsVideo.at(this->videoLowStream);
}
