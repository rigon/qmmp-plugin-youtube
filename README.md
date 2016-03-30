# Qmmp plugin for YouTube
This is a plugin for Qt-based Multimedia Player (Qmmp) to search and play musics directly from YouTube.

## Requirements

This plugin has some requirements, you have to install them:

 - **PythonQt (http://pythonqt.sourceforge.net/)**<br>
   PythonQt is a dynamic Python binding for the Qt framework. It offers an easy way to embed the Python scripting language into your C++ Qt applications.

 - **youtube-dl (https://rg3.github.io/youtube-dl/)**<br>
   youtube-dl is a small command-line program to download videos from YouTube.com and a few more sites.

 - **QJson (http://qjson.sourceforge.net/)**<br>
   QJson is a Qt-based library that maps JSON data to `QVariant` objects and vice versa.

## Installation

First, you have to download the source code by [Downloading a ZIP Archive](https://github.com/rigon/qmmp-plugin-youtube/archive/master.zip) or by cloning the repository:

    git clone https://github.com/rigon/qmmp-plugin-youtube.git

Now, it's time to compile. Move to inside the project location and issue:

    qmake
    make
    sudo cp libyoutube.so /usr/lib/qmmp/General

With the last command, you are installing the library to QMMP's plugin directory.

If you have problems to compile the project, have a look in the section [Known issues](#known-issues).


### HTTP plugin patch

The transport plugin of QMMP does not support HTTPS by default, which is required by the YouTube streams.
So, we have download the source code of the plugin, make the necessary changes, compile it and copy to the QMMP installation:

    wget http://qmmp.ylsoftware.com/files/qmmp-1.0.6.tar.bz2
    tar xvf qmmp-1.0.6.tar.bz2
    cd qmmp-1.0.6/
    patch -p0 < ../http-fix.patch
    cmake .
    make -j4 http

Once completed, install the patched plugin to your QMMP installation path:

    sudo mv /usr/lib/qmmp/Transports/libhttp.so /usr/lib/qmmp/Transports/libhttp.so.bak
    sudo cp src/plugins/Transports/http/libhttp.so /usr/lib/qmmp/Transports/

### ArchLinux users

There is available a package for ArchLinux for this plugin in AUR repository:
https://aur.archlinux.org/packages/qmmp-plugin-youtube/

You can simply install it by running:

    yaourt qmmp-plugin-youtube


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

 - The stream URL of the video is what that is being added to the QMMP's playlist. This causes two problems:
  - the playlist entry is replaced by the URL, making it incomprehensible
  - **the URL becomes invalid after some time**


## Important notes

The plugin is not yet finished, it only has the fundamentals functionalities.
Currently, it is possible to search for videos on Youtube and add them to the selected playlist.

I'm still working on new exciting features, to make it easier to use. I hope soon I will have more news!

If you are interested, you can also contribute to this project, that would be **AWESOME**. Feel free to send me a message.

Checkout the [Issues section](https://github.com/rigon/qmmp-plugin-youtube/issues?q=is%3Aissue+is%3Aopen+label%3Aenhancement) to see the exciting new features that we have planned.
