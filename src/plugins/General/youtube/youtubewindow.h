/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#ifndef YOUTUBEWINDOW_H
#define YOUTUBEWINDOW_H

#include <qt4/QtGui/QWidget>
#include <QString>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ui_youtubewindow.h"

namespace Ui
{
	class YoutubeWindow;
}

class YoutubeWindow : public QDialog
{
    Q_OBJECT
	public:
		YoutubeWindow(QWidget *parent = 0);
		
		~YoutubeWindow();
		
	private slots:
		void buttonSearchClick();
		void buttonAddClick();
		
		void processSearch();
		void processVideo();
		
	private:
		Ui::YoutubeWindow ui;
		
		QStringList selectedTrackInfo;
		QString bestURL;
		int bestURLRanking;
		
		QNetworkAccessManager *searchNetworkManager = NULL;
		QNetworkReply* searchNetworkReply;
		
		QNetworkAccessManager *videoNetworkManager = NULL;
		QNetworkReply* videoNetworkReply;
		
		void processStream(QString data);
};

#endif // YOUTUBEWINDOW_H
