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

#ifndef YOUTUBEUIFACTORY_H
#define YOUTUBEUIFACTORY_H

#include <QObject>
#include <QAction>
#include <QWidget>
#include <QStringList>
#include <QIcon>

#include <qmmpui/general.h>
#include <qmmpui/generalfactory.h>

#include "youtubewindow.h"

class QTranslator;

/**
 * @author Ricardo Gonçalves <ricardompgoncalves@gmail.com>
 */
class YoutubeUIFactory : public QObject, public GeneralFactory
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "org.qmmp.qmmpui.GeneralFactoryInterface.1.0")
Q_INTERFACES(GeneralFactory)

public:
    YoutubeUIFactory(QObject *parent = 0);

    const GeneralProperties properties() const;
    QObject *create(QObject *parent);
    QDialog *createConfigDialog(QWidget *parent);
    void showAbout(QWidget *parent);
    QTranslator *createTranslator(QObject *parent);
};

#endif // YOUTUBEUIFACTORY_H
