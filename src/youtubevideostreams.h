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

#ifndef YOUTUBEVIDEOSTREAMS_H
#define YOUTUBEVIDEOSTREAMS_H

#include <QObject>
#include <QList>
#include <QString>
#include <QNetworkAccessManager>


class YoutubeVideoStreams : public QObject
{
    Q_OBJECT

public:
    class Stream {
    private:
        int ranking;
        QString type;
        QString url;
    public:
        Stream() {}
        Stream(int ranking, QString type, QString url) {
            this->ranking = ranking; this->type = type; this->url = url;
        }

        int getRanking() { return this->ranking; }
        QString getType() { return this->type; }
        QString getUrl() { return this->url; }
    };

protected:
    QNetworkAccessManager *networkManager;

    QString videoId;

    QList<Stream> streamsAudio;
    QList<Stream> streamsVideo;
    int audioHighStream;
    int videoHighStream;
    int audioLowStream;
    int videoLowStream;


    void processStream(QString data);

public:
    explicit YoutubeVideoStreams(QObject *parent = 0);
    ~YoutubeVideoStreams();

signals:
    void streamsAvailable(YoutubeVideoStreams *streams);
    void streamURLAvailable(QString url);

public slots:
    void fetchStreams(QString videoId);

private slots:
    void reply(QNetworkReply *reply);

public:
    QString getVideoId();

    QList<Stream> getStreams();
    Stream getStreamAudioHigh();
    Stream getStreamAudioMedium();
    Stream getStreamAudioLow();
    Stream getStreamVideoHigh();
    Stream getStreamVideoMedium();
    Stream getStreamVideoLow();
};

#endif // YOUTUBEVIDEOSTREAMS_H
