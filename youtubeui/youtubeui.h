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

#ifndef YOUTUBEUI_H
#define YOUTUBEUI_H

#include <QObject>
#include <QAction>
#include <QIcon>

#include "youtubewindow.h"

class YoutubeUI : public QObject
{
    Q_OBJECT

private:
    QAction *m_action_tools;
    QAction *m_action_playlist;
    QAction *m_action_openbrowser;
    YoutubeWindow *m_youtubeWindow = NULL;

public:
    YoutubeUI(QObject *parent = 0);

public slots:
    void showSearchWindow();
    void showRelated();
    void openInBrowser();
    void setFavicon(QIcon *icon);

signals:

};

#endif // YOUTUBEUI_H
