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
#include <unistd.h>

#include "youtubestreamreader.h"
#include "youtubeinputsource.h"
#include "youtubedl.h"

static YoutubeDL *youtubeVideoStreams = NULL;


YoutubeInputSource::YoutubeInputSource(const QString &url, QObject *parent) : InputSource(url, parent)
{
    this->videoID = url.mid(tr("youtube://").length());
}

void YoutubeInputSource::fetchStreamURLComplete(QString url)
{
    std::cout << ">>>>>>>> fetchStreamURLComplete" << std::endl;
    m_reader = new HttpStreamReader(url, this);
    connect(m_reader, SIGNAL(ready()),SIGNAL(ready()));
    connect(m_reader, SIGNAL(error()),SIGNAL(error()));

    m_reader->downloadFile();
}

QIODevice *YoutubeInputSource::ioDevice()
{
    std::cout << ">>>>>>>> ioDevice" << std::endl;
    return m_reader;
}

bool YoutubeInputSource::initialize()
{
    std::cout << ">>>>>>>> initialize" << std::endl;
    if(youtubeVideoStreams == NULL)
       youtubeVideoStreams = new YoutubeDL();

    connect(youtubeVideoStreams, &YoutubeDL::streamURLAvailable, this, &YoutubeInputSource::fetchStreamURLComplete);
    youtubeVideoStreams->fetchStreams(this->videoID);

    return true;
}

bool YoutubeInputSource::isReady()
{
    std::cout << ">>>>>>>> isReady" << std::endl;
    return m_reader->isOpen();
}

bool YoutubeInputSource::isWaiting()
{
    return (!m_reader->bytesAvailable() && m_reader->isOpen());
}

QString YoutubeInputSource::contentType() const
{
    return m_reader->contentType();
}
