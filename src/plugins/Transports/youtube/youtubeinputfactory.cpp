/***************************************************************************
 *   Copyright (C) 2009-2013 by Ilya Kotov                                 *
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

#include <QtPlugin>
#include <QMessageBox>
#include <QTranslator>
#include <curl/curlver.h>
#include <qmmp/qmmp.h>
#include "settingsdialog.h"
#include "youtubeinputsource.h"
#include "youtubeinputfactory.h"

const InputSourceProperties YoutubeInputFactory::properties() const
{
    InputSourceProperties p;
    p.protocols << "youtube";
    p.name = tr("YouTube Plugin");
    p.shortName = "youtube";
    p.hasAbout = true;
    p.hasSettings = true;
    return p;
}

InputSource *YoutubeInputFactory::create(const QString &url, QObject *parent)
{
    return new YoutubeInputSource(url, parent);
}

void YoutubeInputFactory::showSettings(QWidget *parent)
{
    SettingsDialog *s = new SettingsDialog(parent);
    s->show();
}

void YoutubeInputFactory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About YouTube Transport Plugin"),
                        tr("Qmmp YouTube Transport Plugin")+"\n"+
                        tr("Compiled against libcurl-%1").arg(LIBCURL_VERSION) + "\n" +
                        tr("Written by: Ricardo Goncalves <ricar.goncalves@gmail.com>"));
}

QTranslator *YoutubeInputFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/http_plugin_") + locale);
    return translator;
}
Q_EXPORT_PLUGIN2(http, YoutubeInputFactory)
