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

#include <QMessageBox>
#include <QWidgetItem>
#include <QString>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QFile>
#include <iostream>
#include <qjson/parser.h>
#include <qmmpui/playlistmanager.h>
#include <qmmp/qmmp.h>
#include "youtubewindow.h"

YoutubeWindow::YoutubeWindow(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);
    setWindowFlags(Qt::Window);
    //setAttribute(Qt::WA_DeleteOnClose);
	
	connect(ui.textSearch, SIGNAL(returnPressed()), this, SLOT(buttonSearchClick()));
	connect(ui.buttonSearch, SIGNAL(clicked(bool)), this, SLOT(buttonSearchClick()));
	connect(ui.listResults, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(buttonAddClick()));
	connect(ui.buttonAdd, SIGNAL(clicked(bool)), this, SLOT(buttonAddClick()));
	connect(ui.buttonClose, SIGNAL(clicked(QAbstractButton*)), this, SLOT(close()));
	
	ui.labelState->setText("");
}


void YoutubeWindow::buttonSearchClick()
{
	// Base URL
	QUrl url("https://content.googleapis.com/youtube/v3/search?part=snippet&key=AIzaSyCFj15TpkchL4OUhLD1Q2zgxQnMb7v3XaM&type=playlist,video&maxResults=50");
	// Search String
	QString search(ui.textSearch->text());
	
	// Add query parameter to the URL
	url.addQueryItem("q",search.replace(' ','+'));
	
	// Request and specific headers
	QNetworkRequest request;
	request.setUrl(url);
	//request.setRawHeader("Host", "content.googleapis.com");
	//request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0");
	//request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	//request.setRawHeader("Accept-Language", "en-US,en;q=0.5");
	//request.setRawHeader("Accept-Encoding", "gzip, deflate");
	//request.setRawHeader("X-JavaScript-User-Agent", "google-api-javascript-client/1.1.0-beta");
	//request.setRawHeader("X-ClientDetails", "appVersion=5.0%20(X11)&platform=Linux%20x86_64&userAgent=Mozilla%2F5.0%20(X11%3B%20Linux%20x86_64%3B%20rv%3A35.0)%20Gecko%2F20100101%20Firefox%2F35.0");
	request.setRawHeader("X-Origin", "https://developers.google.com");
	//request.setRawHeader("X-Referer", "https://developers.google.com");
	//request.setRawHeader("X-Goog-Encode-Response-If-Executable", "base64");
	//request.setRawHeader("Referer", "https://content.googleapis.com/static/proxy.html?jsh=m%3B%2F_%2Fscs%2Fapps-static%2F_%2Fjs%2Fk%3Doz.gapi.pt_PT.2H_NS8R3WEM.O%2Fm%3D__features__%2Fam%3DAQ%2Frt%3Dj%2Fd%3D1%2Ft%3Dzcms%2Frs%3DAGLTcCP16vYF78SM-2BOkCOIg42VdVq7YQ");
	//request.setRawHeader("Connection", "keep-alive");
	//request.setRawHeader("If-None-Match", "\"F9iA7pnxqNgrkOutjQAa9F2k8HY/H_EGcd-W0Fs1wftFDb5-3dmNY0Q\"");
	
	
	// Detroys previous call if exists
	if(this->searchNetworkManager != NULL)
		this->searchNetworkManager->~QNetworkAccessManager();
	
	this->searchNetworkManager = new QNetworkAccessManager();
	this->searchNetworkReply = this->searchNetworkManager->get(request);  // GET
	connect(searchNetworkReply, SIGNAL(finished()), this, SLOT(processSearch()));
	this->searchNetworkReply->request();
	
	ui.labelState->setText("Searching...");
}

void YoutubeWindow::processSearch()
{
	ui.labelState->setText("Processing results...");
	
	// Reads the reply
	QByteArray reply = this->searchNetworkReply->readAll();
	
	std::cout << QString(reply).toStdString() << std::endl << std::endl << std::endl;
	
	// free networkManager
	this->searchNetworkManager->deleteLater();
	this->searchNetworkManager = NULL;
	
	// Clears the previous search result
	ui.listResults->clear();
	
	// create a json Parser
	QJson::Parser parser;
	QVariantMap result = parser.parse(reply).toMap();
	
	// Iterate over result items
	foreach (QVariant item, result["items"].toList()) {
		QMap<QString, QVariant> map = item.toMap();
		QMap<QString, QVariant> snippet = item.toMap()["snippet"].toMap();
		
		QString id = map["id"].toMap()["videoId"].toString();
		QString title = snippet["title"].toString();
		QString description = snippet["description"].toString();
		QString channel = snippet["channelTitle"].toString();
		QString thumbnail = snippet["thumbnails"].toMap()["high"].toMap()["url"].toString();
		
		QStringList info;
		info.append(id);
		info.append(title);
		info.append(description);
		info.append(channel);
		info.append(thumbnail);
		
		QListWidgetItem *widgetItem = new QListWidgetItem(title, ui.listResults);
		widgetItem->setData(Qt::UserRole, info);
		ui.listResults->addItem(widgetItem);
	}
	
	ui.labelState->setText("");
}

void YoutubeWindow::buttonAddClick() {
	// Base URL
	QUrl url("https://www.youtube.com/watch?");
	
	// Selected Video
	if(ui.listResults->selectedItems().size() != 1) {
		QMessageBox msgBox; msgBox.setText("Select one item!"); msgBox.exec();
		return;
	}
	
	// Info about the selected item
	this->selectedTrackInfo = ui.listResults->selectedItems().at(0)->data(Qt::UserRole).toStringList();
	
	// Video ID
	QString videoId = this->selectedTrackInfo.at(0);
	
	// Add video parameter to the URL
	url.addQueryItem("v",videoId);
	
	// Request and specific headers
	QNetworkRequest request;
	request.setUrl(url);
	//request.setRawHeader("Host", "www.youtube.com");
	//request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0");
	//request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	//request.setRawHeader("Accept-Language", "en-US,en;q=0.5");
	//request.setRawHeader("Accept-Encoding", "gzip, deflate");
	//request.setRawHeader("Cookie", "YSC=XpSfDGuUadY; VISITOR_INFO1_LIVE=ad4l-CZxLLM; PREF=f1=50000000&f5=30; GEUP=b9ae0844ae529881f8545ed7c9d904f9aQcAAAA=; ACTIVITY=1422551889138");
	//request.setRawHeader("Connection", "keep-alive");
	
	// Detroys previous call if exists
	if(this->videoNetworkManager != NULL)
		this->videoNetworkManager->~QNetworkAccessManager();
	
	this->videoNetworkManager = new QNetworkAccessManager();
	this->videoNetworkReply = this->videoNetworkManager->get(request);  // GET
	connect(videoNetworkReply, SIGNAL(finished()), this, SLOT(processVideo()));
	this->videoNetworkReply->request();
	
	ui.labelState->setText("Getting YouTube streams...");
}

void YoutubeWindow::processVideo()
{
	ui.labelState->setText("Processing YouTube streams...");
	
	// Reads the reply
	QByteArray replyBA = this->videoNetworkReply->readAll();
	QString reply = QString(replyBA);
	
	// free networkManager
	this->videoNetworkManager->deleteLater();
	this->videoNetworkManager = NULL;
	
	// Extracts adaptative_fmts from the reply
	int adaptative_fmts_start = reply.indexOf("\"adaptive_fmts\"") + 17;	// strlen( "adaptive_fmts":" ) = 17
	QString adaptative_fmts = reply.mid(
		adaptative_fmts_start,
		reply.indexOf('"', adaptative_fmts_start) - adaptative_fmts_start);
	
	// Extracts url_encoded_fmt_stream_map from the reply
	int url_encoded_fmt_stream_map_start = reply.indexOf("\"url_encoded_fmt_stream_map\"") + 30;	// strlen( "url_encoded_fmt_stream_map":" ) = 30
	QString url_encoded_fmt_stream_map = reply.mid(
		url_encoded_fmt_stream_map_start,
		reply.indexOf('"', url_encoded_fmt_stream_map_start) - url_encoded_fmt_stream_map_start);
	
// 	std::cout << "-- adaptative_fmts" << std::endl;
// 	std::cout << adaptative_fmts.toStdString() << std::endl << std::endl;
// 	std::cout << "-- url_encoded_fmt_stream_map" << std::endl;
// 	std::cout << url_encoded_fmt_stream_map.toStdString() << std::endl;
// 	std::cout << std::endl << std::endl << std::endl << std::endl;
// 	std::cout << reply.toStdString();
	
	// Process URL's and determines the bestURL
	this->bestURL = "";
	this->bestURLRanking = 0;
	this->processStream(adaptative_fmts);
	this->processStream(url_encoded_fmt_stream_map);
	
	// Track MetaData
	QString videoTitle = this->selectedTrackInfo.at(1);
	QString artist = videoTitle.left(videoTitle.indexOf('-')).trimmed();
	QString title = videoTitle.mid(videoTitle.indexOf('-') + 1).trimmed();
	
	FileInfo *fileInfo = new FileInfo(this->bestURL);
	fileInfo->setMetaData(Qmmp::TITLE, title);
	//fileInfo->setMetaData(Qmmp::ALBUM, "My album");
	fileInfo->setMetaData(Qmmp::ARTIST, artist);
	fileInfo->setMetaData(Qmmp::URL, this->bestURL);
	fileInfo->setMetaData(Qmmp::Qmmp::COMMENT, this->selectedTrackInfo.at(2));
	
	// Adds the tack to the currentPlayList
	PlayListTrack *track = new PlayListTrack(fileInfo);
	PlayListManager::instance()->currentPlayList()->add(track);
	
	
 	std::cout << std::endl << "Selected stream URL with ranking " << (this->bestURLRanking) << ":" << std::endl <<
		(this->bestURL.toStdString()) << std::endl <<
		"Title: " << title.toStdString() << std::endl <<
		"Artist: " << artist.toStdString() << std::endl <<
		"Video ID: " << this->selectedTrackInfo.at(0).toStdString() << std::endl <<
		"Description: " << selectedTrackInfo.at(2).toStdString() << std::endl <<
		"Channel: " << selectedTrackInfo.at(3).toStdString() << std::endl <<
		"Thumbnail: " << selectedTrackInfo.at(4).toStdString() << std::endl;
	
	
	ui.labelState->setText("Track added!");
}

void YoutubeWindow::processStream(QString data)
{
	QStringList streams = data.split(",");
	foreach(QString stream, streams) {
		QString tmpURL;
		int ranking = 1;
		
		QStringList params = stream.split("\\u0026");
		foreach(QString param, params) {
			//std::cout << param.toStdString() << std::endl;
			
			param = QUrl::fromPercentEncoding(param.toAscii());
			param = param.replace('+',' ');
			
			std::cout << param.toStdString() << std::endl;
			
			if(param.startsWith("url="))
				tmpURL = param.mid(4);	// Removes "url="
			else if(param.startsWith("type=")) {
				QString value = param.mid(5);
				if(value.startsWith("audio"))
					ranking += 10000000;
				if(value.startsWith("audio/mp4"))
					ranking += 10000000;
			}
			else if(param.startsWith("bitrate="))
				ranking += param.mid(8).toInt();
			else if(param.startsWith("quality=")) {
				QString value = param.mid(8);
				if(value == "small")
					ranking += 200000;
				if(value == "medium")
					ranking += 600000;
				if(value == "high")
					ranking += 1000000;
			}
		}
		std::cout << "Ranking: " << ranking << std::endl;
		
		if(ranking > this->bestURLRanking) {
			this->bestURLRanking = ranking;
			this->bestURL = tmpURL;
		}
		
		std::cout << std::endl;
	}
}

YoutubeWindow::~YoutubeWindow()
{
}
