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

#include <iostream>

#include <PythonQt/PythonQt.h>
#include <QMessageBox>
#include <QObject>

#include "youtubedl.h"

static QString script =
    "import sys\n"
    "sys.path.append('/usr/lib/python3.5/site-packages')\n"
    "from youtube_dl import YoutubeDL\n"
    "\n"
    "def get_stream(id):\n"
    "    with YoutubeDL() as ydl:\n"
    "        result = ydl.extract_info(\n"
    "            'http://www.youtube.com/watch?v=%s' % id,\n"
    "            download=False # We just want to extract the info\n"
    "        )\n"
    "    \n"
    "    if 'entries' in result:\n"
    "        # Can be a playlist or a list of videos\n"
    "        video = result['entries'][0]\n"
    "    else:\n"
    "        # Just a video\n"
    "        video = result\n"
    "    \n"
    "    abr = 0\n"
    "    for stream in video['formats']:\n"
    "        if stream['ext'] == 'm4a' and stream['abr'] > abr:\n"
    "            abr = stream['abr']\n"
    "            beststream = stream\n"
    "    \n"
    "    return beststream['url']\n";

/*
static QString script2 =
    "import sys\n"
    "sys.path.append('/usr/lib/python3.5/site-packages')\n"
    "from youtube_dl import YoutubeDL\n"
    "\n"
    "def get_stream(id):\n"
    "    print id\n"
    "    return id\n";

//    QMessageBox::information(NULL, "Restul", result.toString());
//    QList<QVariant> list = result.toList();
//    foreach(QVariant s, list)
//        QMessageBox::information(NULL, "Result", s.toString());
*/

YoutubeDL::YoutubeDL()
{
    this->initialize();
}

void YoutubeDL::initialize()
{
    std::cout << ">> Init Python..." << std::endl;

    // init PythonQt and Python itself
    PythonQt::init();

    // get a smart pointer to the __main__ module of the Python interpreter
    context = PythonQt::self()->getMainModule();

    // Evaluate script
    context.evalScript(script);
}

void YoutubeDL::fetchStreams(QString videoId) {
    this->videoId = videoId;

    // Start the thread to run the script
//    this->start();
    this->run();
}


void YoutubeDL::run()
{
    // Call Pyhthon Script to determine the URL
    // Arguments to pass
    QVariantList args;
    args << this->videoId;

    std::cout << ">> Running the Python script for VideoID " << this->videoId.toStdString() << "..." << std::endl;

    // Run the script
    QVariant result = context.call("get_stream", args);
    QString streamURL = result.toString();

    std::cout << ">> The resulting URL is: " << streamURL.toStdString() << std::endl;

    // Emits a signal
    emit streamURLAvailable(streamURL);


    // Process results
    Stream streamObj(0, "audio/m4a", streamURL);
    this->streamsAudio.append(streamObj);
    // Emits a signal
    emit streamsAvailable(this);
}
