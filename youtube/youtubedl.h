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

#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QString>
#include <QObject>
#include <PythonQt/PythonQt.h>

class YoutubeDL : public QObject
{
    Q_OBJECT

private:
    PythonQtObjectPtr context;

public:
    YoutubeDL();
    ~YoutubeDL();

public slots:
    void fetchStreams(QString videoId);

signals:
    void streamURLAvailable(QString url);
};

#endif // YOUTUBEDL_H
