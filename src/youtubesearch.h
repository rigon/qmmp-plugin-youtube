#ifndef YOUTUBESEARCH_H
#define YOUTUBESEARCH_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>


class YoutubeSearch : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *networkManager;

public:
    explicit YoutubeSearch(QObject *parent = 0);
    ~YoutubeSearch();

signals:
    void resultsAvailable(QJsonObject *result);

public slots:
    void search(QString search);

private slots:
    void reply(QNetworkReply *reply);
};

#endif // YOUTUBESEARCH_H
