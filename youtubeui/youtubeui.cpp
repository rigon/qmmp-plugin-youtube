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

#include <QObject>
#include <QMessageBox>
#include <QTranslator>
#include <QList>
#include <QDesktopServices>

#include <qmmpui/uihelper.h>
#include <qmmpui/mediaplayer.h>
#include <qmmpui/playlistmanager.h>
#include <qmmpui/playlisttrack.h>

#include "qurlimage.h"
#include "youtubeuifactory.h"
#include "youtubepreferences.h"
#include "youtubewindow.h"
#include "youtubeui.h"

YoutubeUI::YoutubeUI(QObject *parent) : QObject(parent)
{
    // Create Youtube Window
    m_youtubeWindow = new YoutubeWindow();

    // Show search window from Tools menu
    m_action_tools = new QAction(tr("YouTube"), this);
    m_action_tools->setShortcut(tr("Ctrl+Y"));
    UiHelper::instance()->addAction(m_action_tools, UiHelper::TOOLS_MENU);
    connect(m_action_tools, &QAction::triggered, this, &YoutubeUI::showSearchWindow);

    // Show related videos from the playlist context menu
    m_action_playlist = new QAction(tr("Search track"), this);
    m_action_playlist->setShortcut(tr("Meta+Y"));
    UiHelper::instance()->addAction(m_action_playlist, UiHelper::PLAYLIST_MENU);
    connect (m_action_playlist, &QAction::triggered, this, &YoutubeUI::showRelated);

    // Open video in the browser from the playlist context menu
    m_action_openbrowser = new QAction(tr("Open in browser"), this);
    m_action_openbrowser->setIcon(QIcon::fromTheme("applications-internet"));
    UiHelper::instance()->addAction(m_action_openbrowser, UiHelper::PLAYLIST_MENU);
    connect (m_action_openbrowser, &QAction::triggered, this, &YoutubeUI::openInBrowser);

    // Youtube Icon
    QUrlImage *favicon = new QUrlImage();
    connect(favicon, &QUrlImage::finishedIcon, this, &YoutubeUI::setFavicon);
    favicon->fetchUrl("https://www.youtube.com/favicon.ico");
}

void YoutubeUI::setFavicon(QIcon *icon)
{
    m_youtubeWindow->setWindowIcon(*icon);
    m_action_tools->setIcon(*icon);
    m_action_playlist->setIcon(*icon);
    delete icon;
}


void YoutubeUI::showSearchWindow()
{
    static bool firstTime = true;

    m_youtubeWindow->show();
    m_youtubeWindow->activateWindow();
    if(firstTime) m_youtubeWindow->searchFor(NULL);
    firstTime = false;
}

void YoutubeUI::showRelated()
{
    // List of selected tracks
    PlayListManager *pl_manager = MediaPlayer::instance()->playListManager();
    QList <PlayListTrack *> tracks = pl_manager->selectedPlayList()->selectedTracks();

    // If at least a track is selected
    if (!tracks.isEmpty()) {
        // First track selected
        QString videoTitle(tracks.at(0)->value(Qmmp::ARTIST) + " - " + tracks.at(0)->value(Qmmp::TITLE));

        m_youtubeWindow->show();
        m_youtubeWindow->activateWindow();
        m_youtubeWindow->searchFor(videoTitle);
    }
}

void YoutubeUI::openInBrowser()
{
    // List of selected tracks
    PlayListManager *pl_manager = MediaPlayer::instance()->playListManager();
    QList <PlayListTrack *> tracks = pl_manager->selectedPlayList()->selectedTracks();

    // If at least a track is selected
    if (!tracks.isEmpty()) {
        // First track selected
        QString url(tracks.at(0)->value(Qmmp::URL));

        if(url.startsWith("youtube://")) {
            QString videoID(url.mid(tr("youtube://").length()));
            QDesktopServices::openUrl(QUrl("https://www.youtube.com/watch?v=" + videoID));
        }
        else
            QMessageBox::about(NULL, tr("YouTube Plugin"), tr("The selected track is not a YouTube video!"));
    }
}
