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
