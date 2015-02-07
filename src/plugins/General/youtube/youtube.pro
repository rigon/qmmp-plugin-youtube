include(../../plugins.pri)

INCLUDEPATH += ../../../../src
CONFIG += warn_on \
plugin

TARGET =$$PLUGINS_PREFIX/General/youtube
unix:QMAKE_CLEAN = $$PLUGINS_PREFIX/General/libyoutube.so


TEMPLATE = lib
unix:QMAKE_LIBDIR += ../../../../lib:/usr/lib
unix:LIBS += -lqmmpui -lqmmp -lqjson

win32:QMAKE_LIBDIR += ../../../../bin
win32:LIBS += -lqmmpui0 -lqmmp0 -lqjson

TRANSLATIONS = translations/streambrowser_plugin_cs.ts \
               translations/streambrowser_plugin_de.ts \
               translations/streambrowser_plugin_zh_CN.ts \
               translations/streambrowser_plugin_zh_TW.ts \
               translations/streambrowser_plugin_ru.ts \
               translations/streambrowser_plugin_pl.ts \
               translations/streambrowser_plugin_uk_UA.ts \
               translations/streambrowser_plugin_it.ts \
               translations/streambrowser_plugin_tr.ts \
               translations/streambrowser_plugin_lt.ts \
               translations/streambrowser_plugin_nl.ts \
               translations/streambrowser_plugin_ja.ts \
               translations/streambrowser_plugin_es.ts \
               translations/streambrowser_plugin_sr_BA.ts \
               translations/streambrowser_plugin_sr_RS.ts
RESOURCES = translations/translations.qrc
	unix{
	isEmpty(LIB_DIR){
		LIB_DIR = /lib
	}
	target.path = $$LIB_DIR/qmmp/General
	INSTALLS += target
}

HEADERS += youtubefactory.h \
           youtube.h \
           youtubewindow.h

win32:HEADERS += ../../../../src/qmmpui/general.h
SOURCES += youtubefactory.cpp \
           youtube.cpp \
           youtubewindow.cpp

FORMS += youtubewindow.ui

QT += network

