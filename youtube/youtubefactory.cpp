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

#include "youtubefactory.h"
#include "youtubeinputsource.h"

YoutubeFactory::YoutubeFactory(QObject *parent) : QObject(parent)
{

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
    QMessageBox::about(parent, tr("YouTube Plugin"),
                        tr("No settings to show"));
}

void YoutubeFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About YouTube Plugin"),
                        tr("Qmmp YouTube Plugin")+"\n"+
                        tr("This plugin allows to play musics directly from YouTube videos")+"\n"+
                        tr("Written by: Ricardo Gonçalves <ricardompgoncalves@gmail.com>"));
}

QTranslator *YoutubeFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/youtube_plugin_") + locale);
    return translator;
}
