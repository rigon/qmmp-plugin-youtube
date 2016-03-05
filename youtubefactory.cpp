/***************************************************************************
 *   Copyright (C) 2012 by Ilya Kotov                                      *
 *   forkotov02@hotmail.ru                                                 *
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

#include "youtube.h"
#include "youtubefactory.h"
#include "youtubepreferences.h"


const GeneralProperties YoutubeFactory::properties() const
{
    GeneralProperties properties;
    properties.name = tr("YouTube Plugin");
    properties.shortName = "youtube";
    properties.hasAbout = true;
    properties.hasSettings = false;     // TODO: Change to true
    properties.visibilityControl = false;
    return properties;
}

QObject *YoutubeFactory::create(QObject *parent)
{
    return new Youtube(parent);
}

QDialog *YoutubeFactory::createConfigDialog(QWidget *parent)
{
    return new YoutubePreferences(parent);
}

void YoutubeFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About YouTube Plugin"),
                        tr("Qmmp YouTube Plugin")+"\n"+
                        tr("This plugin allows to play musics and playlists from YouTube")+"\n"+
                        tr("Written by: Ricardo Gonçalves <ricardompgoncalves@gmail.com>"));
}

QTranslator *YoutubeFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/streambrowser_plugin_") + locale);
    return translator;
}
