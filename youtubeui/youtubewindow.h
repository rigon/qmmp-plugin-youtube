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

#ifndef YOUTUBEWINDOW_H
#define YOUTUBEWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QKeyEvent>
#include <QJsonObject>

#include "ui_youtubewindow.h"

namespace Ui {
    class YoutubeWindow;
}

class YoutubeWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::YoutubeWindow *ui;

    QStringList selectedTrackInfo;

public:
    YoutubeWindow(QWidget *parent = 0);
    ~YoutubeWindow();

private slots:
    void on_buttonSearch_clicked();
    void on_buttonSearchRelated_clicked();
    void on_buttonAdd_clicked();
    void on_buttonPreferences_clicked();

    void processSearch(QJsonObject *result);

public slots:
    void searchFor(QString videoTitle);
};

#endif // YOUTUBEWINDOW_H
