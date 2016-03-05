#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QString>
#include <QThread>

#include "youtubevideostreams.h"

class YoutubeDL : public YoutubeVideoStreams, public QThread
{

protected:
    void run();

public:
    void fetchStreams(QString videoId);
};


#endif // YOUTUBEDL_H
