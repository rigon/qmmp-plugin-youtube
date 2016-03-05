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
