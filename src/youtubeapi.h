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

#ifndef YOUTUBEAPI_H
#define YOUTUBEAPI_H

#include <QObject>
#include <QString>
#include <QMetaMethod>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>


#define YOUTUBE_API(resource)   "https://www.googleapis.com/youtube/v3/" # resource
#define YOUTUBE_API_SEARCH      YOUTUBE_API(search)
#define YOUTUBE_API_VIDEOS      YOUTUBE_API(videos)


class YoutubeAPI : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *networkManager;
    void runRequest(const char *url, QUrlQuery &urlQuery, void (YoutubeAPI::*method)(QNetworkReply *));

public:
    explicit YoutubeAPI(QObject *parent = 0);
    ~YoutubeAPI();

public slots:
    void searchList(QString queryTerm);
    void searchRelated(QString id);
    void videosList(QString id);

private slots:
    void replySearchList(QNetworkReply *reply);
    void replyVideosList(QNetworkReply *reply);

signals:
    void resultsAvailable(QJsonObject *result);
    void resultsVideosListAvailable(QString result);

};

#endif // YOUTUBEAPI_H
