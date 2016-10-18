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
#include <QImage>
#include <QIcon>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "qurlimage.h"


QUrlImage::QUrlImage()
{

}

QUrlImage::QUrlImage(QString url) : QUrlImage(QUrl(url))
{

}

QUrlImage::QUrlImage(QUrl url)
{
    this->fetchUrl(url);
}


void QUrlImage::fetchUrl(QString url)
{
    this->fetchUrl(QUrl(url));
}

void QUrlImage::fetchUrl(QUrl url)
{
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &QUrlImage::requestFinished);
    networkManager->get(QNetworkRequest(url));
}


void QUrlImage::requestFinished(QNetworkReply *reply)
{
    // Reading attributes of the reply
    // e.g. the HTTP status code
    //QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // Or the target URL if it was a redirect:
    //QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here
        QByteArray bytes = reply->readAll();  // bytes
        image = new QImage();
        image->loadFromData(bytes);

        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        icon = new QIcon(pixmap);

        emit finishedImage(image);
        emit finishedIcon(icon);
    }
    else
    {
        // handle errors here
    }

    waitFinish.release();

    // We receive ownership of the reply object and therefore need to handle deletion.
    delete reply;
}

QImage *QUrlImage::getImage() {
    waitFinish.acquire();
    QImage *retImage = this->image;
    waitFinish.release();

    return retImage;
}

QIcon *QUrlImage::getIcon() {
    waitFinish.acquire();
    QIcon *retIcon = this->icon;
    waitFinish.release();

    return retIcon;
}

QUrlImage::~QUrlImage()
{

}
