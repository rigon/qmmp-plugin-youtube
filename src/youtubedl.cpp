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

void YoutubeDL::fetchStreams(QString videoId) {
    this->videoId = videoId;

    // Start the thread to run the script
    this->start();
}


void YoutubeDL::run() {

    // init PythonQt and Python itself
    PythonQt::init();

    // get a smart pointer to the __main__ module of the Python interpreter
    PythonQtObjectPtr context = PythonQt::self()->getMainModule();

    // Arguments to pass
    QVariantList args;
    args << this->videoId;

    // Run the script
    context.evalScript(script);
    QVariant result = context.call("get_stream", args);

    // Process results
    Stream streamObj(0, "audio/m4a", result.toString());
    this->streamsAudio.append(streamObj);

    // Emits a signal
    emit streamsAvailable(this);
}


QString YoutubeDL::runSynchronized(QString videoID)
{
    std::cout << ">> Init Python..." << std::endl;

    // init PythonQt and Python itself
    PythonQt::init();

    // get a smart pointer to the __main__ module of the Python interpreter
    PythonQtObjectPtr context = PythonQt::self()->getMainModule();

    // Arguments to pass
    QVariantList args;
    args << videoID;

    // Run the script
    std::cout << ">> Running the Python script for VideoID " << videoID.toStdString() << "..." << std::endl;
    context.evalScript(script);
    QVariant result = context.call("get_stream", args);
    QString streamURL = result.toString();

    std::cout << ">> The calculated URL is: " << streamURL.toStdString() << std::endl;

    // Return the stream URL
    return streamURL;
}
