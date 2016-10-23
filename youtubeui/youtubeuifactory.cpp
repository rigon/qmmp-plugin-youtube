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
#include "youtubeui.h"
#include "youtubepreferences.h"
#include "youtubewindow.h"
#include "youtubeuifactory.h"


YoutubeUIFactory::YoutubeUIFactory(QObject *parent) : QObject(parent)
{

}

const GeneralProperties YoutubeUIFactory::properties() const
{
    GeneralProperties p;
    p.name = tr("YouTubeUI Plugin");
    p.shortName = "youtubeui";
    p.hasAbout = true;
    p.hasSettings = true;     // TODO: Change to true
    //p.visibilityControl = false;
    return p;
}

QObject *YoutubeUIFactory::create(QObject *parent)
{
    return new YoutubeUI(parent);
}

QDialog *YoutubeUIFactory::createConfigDialog(QWidget *parent)
{
    return new YoutubePreferences(parent);;
}

void YoutubeUIFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About YouTube Plugin"),
        tr("Qmmp YouTube Plugin")+"\n"+
        tr("This plugin allows to play musics directly from YouTube videos")+"\n"+
        tr("Written by: Ricardo Gonçalves <ricardompgoncalves@gmail.com>"));
}

QTranslator *YoutubeUIFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/youtube_plugin_") + locale);
    return translator;
}
