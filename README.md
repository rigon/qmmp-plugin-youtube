# Qmmp plugin for YouTube
This is a plugin for Qt-based Multimedia Player (Qmmp) to search and play musics directly from YouTube.

## Requirements

This plugin has some requirements, you have to install them:

PythonQt (http://pythonqt.sourceforge.net/)
  : PythonQt is a dynamic Python binding for the Qt framework. It offers an easy way to embed the Python scripting language into your C++ Qt applications.

youtube-dl (https://rg3.github.io/youtube-dl/)
  : youtube-dl is a small command-line program to download videos from YouTube.com and a few more sites.

QJson (http://qjson.sourceforge.net/)
  : QJson is a Qt-based library that maps JSON data to `QVariant` objects and vice versa.

## Installation

First, you have to download the source code by [Downloading a ZIP Archive](https://github.com/rigon/qmmp-plugin-youtube/archive/master.zip) or by cloning the repository:

    git clone https://github.com/rigon/qmmp-plugin-youtube.git

Now, it's time to compile. Move to inside the project location and issue:

    qmake
    make
    sudo cp libyoutube.so /usr/lib/qmmp/General

With the last command, you are installing the library to QMMP's plugin directory.

If you have problems to compile the project, have a look in the section *Known issues*.


## Configuration

Open QMMP. Now you have to activate the Youtube plugin. 
To do so, you have to do the next steps:

**Settings** > **Plugins** > **General** > Check **Youtube Plugin**

Now, the Youtube plugin is accessible from the menu inside **Tools** option. Or you can press **Ctrl + Y** for quick access.

## Known issues

 - The Python version is hard coded, the version used was ``python 3.5m``. If you have a different version installed, edit the following files and change the referenced lines accordingly:

  - ``youtube.pro``:

            INCLUDEPATH += /usr/include/python3.5m

  - ``src/youtubedl.cpp``:

            "sys.path.append('/usr/lib/python3.5/site-packages')\n"

 - The stream URL of the video is what that is being added to the QMMP's playlist. This causes two problems: the playlist entry is replaced by the URL, making it incomprehensible and URL becomes invalid after some time.


## Important notes

The plugin is not yet finished, it only has the fundamentals functionalities.
Currently, it is possible to search for videos on Youtube and add them to the selected playlist.

I'm still working on new exciting features, to make it easier to use. I hope soon I will have more news!

If you are interested, you can also contribute to this project, that would be **AWESOME**. Feel free to send me a message.
