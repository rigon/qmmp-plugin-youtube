#ifndef QURLIMAGE_H
#define QURLIMAGE_H

#include <QImage>
#include <QIcon>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSemaphore>


class QUrlImage : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager* networkManager;
    QSemaphore waitFinish;
    QImage *image;
    QIcon *icon;

public:
    QUrlImage();
    QUrlImage(QString url);
    QUrlImage(QUrl url);

    void fetchUrl(QString url);
    void fetchUrl(QUrl url);
    QImage *getImage();
    QIcon *getIcon();

    ~QUrlImage();

private slots:
    void requestFinished(QNetworkReply* reply);

signals:
    void finishedImage(QImage *image);
    void finishedIcon(QIcon *icon);

};

#endif // QURLIMAGE_H
