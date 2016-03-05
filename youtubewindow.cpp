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
#include <QDialog>
#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <qmmp/fileinfo.h>
#include <qmmpui/playlistmanager.h>
#include <time.h>

#include "youtubepreferences.h"
#include "youtubewindow.h"
#include "youtubesearch.h"
#include "youtubevideostreams.h"
#include "youtubedl.h"

#include <iostream>

time_t searchTime = 0;


YoutubeWindow::YoutubeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YoutubeWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    //setAttribute(Qt::WA_DeleteOnClose);

    ui->buttonPreferences->setVisible(false);   // TODO: Remove this line

    // Search on open
    this->on_buttonSearch_clicked();
}

void YoutubeWindow::on_buttonSearch_clicked()
{
    time_t currentTime = time(NULL);
    if(currentTime - searchTime < 1)   // Limit to 1 request per second
        return;
    searchTime = currentTime;


    ui->labelState->setText("Searching...");

    // Search String
    QString search(ui->textSearch->text());

    YoutubeSearch *youtubeSearch = new YoutubeSearch();
    connect(youtubeSearch, &YoutubeSearch::resultsAvailable, this, &YoutubeWindow::processSearch);
    youtubeSearch->search(search);
}


void YoutubeWindow::processSearch(QJsonObject *result)
{
    // Clear previous results
    ui->listResults->clear();

    // Get list of results
    QJsonArray items = result->value("items").toArray();

    // Iterate over result items
    foreach (QVariant item, items) {
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

        QListWidgetItem *widgetItem = new QListWidgetItem(title, ui->listResults);
        widgetItem->setData(Qt::UserRole, info);
        ui->listResults->addItem(widgetItem);
    }

    ui->labelState->setText("");
}

void YoutubeWindow::on_buttonAdd_clicked()
{
    time_t currentTime = time(NULL);
    if(currentTime - searchTime < 1)   // Limit to 1 request per second
        return;
    searchTime = currentTime;


    // Selected Video
    if(ui->listResults->selectedItems().size() != 1) {
        QMessageBox msgBox;
        msgBox.setText("Select one item first!");
        msgBox.exec();
        return;
    }

    ui->labelState->setText("Getting YouTube streams...");

    // Info about the selected item
    this->selectedTrackInfo = ui->listResults->selectedItems().at(0)->data(Qt::UserRole).toStringList();

    // Video ID
    QString videoId = this->selectedTrackInfo.at(0);

    YoutubeDL *youtubeVideoStreams = new YoutubeDL();
    connect(youtubeVideoStreams, &YoutubeDL::streamsAvailable, this, &YoutubeWindow::addTrack);
    youtubeVideoStreams->fetchStreams(videoId);
}

void YoutubeWindow::addTrack(YoutubeVideoStreams *streams)
{
    // Track MetaData
    QString videoTitle = this->selectedTrackInfo.at(1);
    QString artist = videoTitle.left(videoTitle.indexOf('-')).trimmed();
    QString title = videoTitle.mid(videoTitle.indexOf('-') + 1).trimmed();

    YoutubeVideoStreams::Stream stream = streams->getStreamAudioHigh();

    FileInfo *fileInfo = new FileInfo(stream.getUrl());
    fileInfo->setMetaData(Qmmp::TITLE, title);
    //fileInfo->setMetaData(Qmmp::ALBUM, "My album");
    fileInfo->setMetaData(Qmmp::ARTIST, artist);
    fileInfo->setMetaData(Qmmp::URL, stream.getUrl());
    fileInfo->setMetaData(Qmmp::COMMENT, this->selectedTrackInfo.at(2));

    // Adds the tack to the currentPlayList
    PlayListTrack *track = new PlayListTrack(fileInfo);
    PlayListManager::instance()->selectedPlayList()->add(track);

    std::cout << std::endl << "Selected stream URL with ranking " << stream.getRanking() << ":" << std::endl <<
        stream.getUrl().toStdString() << std::endl <<
        "Title: " << title.toStdString() << std::endl <<
        "Artist: " << artist.toStdString() << std::endl <<
        "Video ID: " << this->selectedTrackInfo.at(0).toStdString() << std::endl <<
        "Description: " << selectedTrackInfo.at(2).toStdString() << std::endl <<
        "Channel: " << selectedTrackInfo.at(3).toStdString() << std::endl <<
        "Thumbnail: " << selectedTrackInfo.at(4).toStdString() << std::endl;


    ui->labelState->setText("Track added!");

    // QMessageBox::information(this, "Youtube stream URL", stream.getUrl());
}

void YoutubeWindow::on_buttonPreferences_clicked()
{
    YoutubePreferences *youtubePreferences = new YoutubePreferences();
    youtubePreferences->show();
}

YoutubeWindow::~YoutubeWindow() {

}

