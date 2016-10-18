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

#include <qmmpui/uihelper.h>
#include <qmmpui/mediaplayer.h>
#include <qmmpui/playlistmanager.h>
#include <qmmpui/playlisttrack.h>

#include "qurlimage.h"
#include "youtubefactory.h"
#include "youtubepreferences.h"
#include "youtubeinputsource.h"
#include "youtubewindow.h"


YoutubeFactory::YoutubeFactory(QObject *parent) : QObject(parent)
{
    // Create Youtube Window
    m_youtubeWindow = new YoutubeWindow();

    // Show search window from Tools menu
    m_action_tools = new QAction(tr("YouTube"), this);
    m_action_tools->setShortcut(tr("Ctrl+Y"));
    UiHelper::instance()->addAction(m_action_tools, UiHelper::TOOLS_MENU);
    connect(m_action_tools, &QAction::triggered, this, &YoutubeFactory::showSearchWindow);

    // Show related videos from the playlist context menu
    m_action_playlist = new QAction(tr("Search on YouTube"), this);
    m_action_playlist->setShortcut(tr("Meta+Y"));
    UiHelper::instance()->addAction(m_action_playlist, UiHelper::PLAYLIST_MENU);
    connect (m_action_playlist, &QAction::triggered, this, &YoutubeFactory::showRelated);

    // Youtube Icon
    QUrlImage *favicon = new QUrlImage();
    connect(favicon, &QUrlImage::finishedIcon, this, &YoutubeFactory::setFavicon);
    favicon->fetchUrl("https://www.youtube.com/favicon.ico");
}

void YoutubeFactory::setFavicon(QIcon *icon)
{
    m_youtubeWindow->setWindowIcon(*icon);
    m_action_tools->setIcon(*icon);
    m_action_playlist->setIcon(*icon);
    delete icon;
}

const InputSourceProperties YoutubeFactory::properties() const
{
    InputSourceProperties p;
    p.protocols << "youtube";
    p.name = tr("YouTube Plugin");
    p.shortName = "youtube";
    p.hasAbout = true;
    p.hasSettings = true;     // TODO: Change to true
    //p.visibilityControl = false;
    return p;
}

InputSource *YoutubeFactory::create(const QString &url, QObject *parent)
{
    return new YoutubeInputSource(url, parent);
}

void YoutubeFactory::showSettings(QWidget *parent)
{
    YoutubePreferences *preferences = new YoutubePreferences(parent);
    preferences->show();
}

void YoutubeFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About YouTube Plugin"),
                        tr("Qmmp YouTube Plugin")+"\n"+
                        tr("This plugin allows to play musics directly from YouTube videos")+"\n"+
                        tr("Written by: Ricardo Gonçalves <ricardompgoncalves@gmail.com>"));
}

void YoutubeFactory::showSearchWindow()
{
    static bool firstTime = true;

    m_youtubeWindow->show();
    m_youtubeWindow->activateWindow();
    if(firstTime) m_youtubeWindow->searchFor(NULL);
    firstTime = false;
}

void YoutubeFactory::showRelated()
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

QTranslator *YoutubeFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/youtube_plugin_") + locale);
    return translator;
}
