# Qmmp plugin for YouTube
Plugin for [Qmmp (Qt-based Multimedia Player)](http://qmmp.ylsoftware.com) to search and play musics directly from YouTube.


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

Now, let's compile. Extract the files (if necessary) and move to inside the project location.
Then, run the following commands:

	qmake
	make -j4
	
Lastly, copy the newly compiled libraries into  to QMMP's plugin directory:

	sudo cp -v youtube/libyoutube.so /usr/lib/qmmp/Transports
	sudo cp -v youtubeui/libyoutubeui.so /usr/lib/qmmp/General

If you have problems to compile the project, have a look in the [issues section](//github.com/rigon/qmmp-plugin-youtube/labels/issue).


### ArchLinux users

There is available a package for ArchLinux for this plugin in AUR repository:
https://aur.archlinux.org/packages/qmmp-plugin-youtube/

You can simply install it by running:

	yaourt qmmp-plugin-youtube


## Configuration

Open QMMP. Now you have to activate the Youtube plugin.
To do so, you have to do the next steps:

**QMMP main menu** > **Settings** > **Plugins** 

and activate this two plugins:

 - **Youtube Plugin** (libyoutube.so under the **Transports** section)
 - **YoutubeUI Plugin** (libyoutubeui.so under the **General** section)

Now, the Youtube plugin is accessible from the menu inside **Tools** option (you can press **Ctrl + Y** for quicker access). Alternatively, you can search for the selected track from the **track's context menu** > **Actions** > **Search track** (or using the shortcut **Meta + Y**).


## Important notes

The plugin is not yet finished, but it is in a stage that is already usable.
Currently, it is possible to search for videos on Youtube and add them to the selected playlist, search for similar videos and open them in the browser.

If you are interested, you can also contribute to this project, that would be **AWESOME**. Feel free to send me a message.

Checkout the [Issues section](https://github.com/rigon/qmmp-plugin-youtube/issues?q=is%3Aissue+is%3Aopen+label%3Aenhancement) to see the exciting new features that we have planned.


## License info

This software is distributed under [GNU General Public License, version 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).

Any misuse or violation of [Terms of Service of Youtube](https://www.youtube.com/static?template=terms) are the entire responsability of the user of this software.

The user of this software accepts this terms by using this software.
