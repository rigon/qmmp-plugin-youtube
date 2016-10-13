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

#ifndef HTTPINPUTSOURCE_H
#define HTTPINPUTSOURCE_H

#include <qmmp/inputsource.h>

#include "youtubedl.h"

class HttpStreamReader;

/**
 *   @author Ricardo Gonçalves <ricardompgoncalves@gmail.com>
 */
class YoutubeInputSource : public InputSource
{
Q_OBJECT
public:
    YoutubeInputSource(const QString &url, QObject *parent = 0);

    QIODevice *ioDevice();
    bool initialize();
    bool isReady();
    bool isWaiting();
    QString contentType() const;

private:
    HttpStreamReader *m_reader = NULL;
    QString videoID;

private slots:
    void fetchStreamURLComplete(QString url);
    void fetchVideoMetaDataComplete(QHash<QString, QString> videoData);
};

#endif // HTTPINPUTSOURCE_H
