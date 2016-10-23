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

#ifndef YOUTUBEPREFERENCES_H
#define YOUTUBEPREFERENCES_H

#include <QDialog>
#include <QWidget>
#include <QString>


namespace Ui {
    class YoutubePreferences;
}

class YoutubePreferences : public QDialog
{
    Q_OBJECT

private:
    Ui::YoutubePreferences *ui;

    static bool loadedConfiguration;
    static QString youtubeKey;
    static int quality;
    static bool playVideo;
    static int saveMusic;
    static QString saveLocation;

    void accept();

public:
    explicit YoutubePreferences(QWidget *parent = 0);
    ~YoutubePreferences();

    static void readConfiguration(bool forceReload = false);
    // Getters
    static QString getYoutubeKey();
    static int getQuality();
    static bool getPlayVideo();
    static int getSaveMusic();
    static QString getSaveLocation();


private slots:
    void on_comboSaveMusic_currentIndexChanged(int index);
    void on_buttonSaveLocation_clicked();
};

#endif // YOUTUBEPREFERENCES_H
