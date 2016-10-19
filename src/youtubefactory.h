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

#ifndef YOUTUBEFACTORY_H
#define YOUTUBEFACTORY_H

#include <QObject>
#include <QAction>
#include <QStringList>
#include <QIcon>

#include <qmmp/inputsourcefactory.h>

#include "youtubewindow.h"

class QTranslator;

/**
 * @author Ricardo Gonçalves <ricardompgoncalves@gmail.com>
 */
class YoutubeFactory : public QObject, InputSourceFactory
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "org.qmmp.qmmp.InputSourceFactoryInterface.1.0")
Q_INTERFACES(InputSourceFactory)

private:
    QAction *m_action_tools;
    QAction *m_action_playlist;
    QAction *m_action_openbrowser;
    YoutubeWindow *m_youtubeWindow = NULL;

public:
    YoutubeFactory(QObject *parent = 0);

    const InputSourceProperties properties() const;
    InputSource *create(const QString &url, QObject *parent = 0);

    void showSettings(QWidget *parent);
    void showAbout(QWidget *parent);
    QTranslator *createTranslator(QObject *parent);

private slots:
    void showSearchWindow();
    void showRelated();
    void openInBrowser();
    void setFavicon(QIcon *icon);
};

#endif // YOUTUBEFACTORY_H
