#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T04:29:04
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = youtube
TEMPLATE = lib

INCLUDEPATH += /usr/include/python3.5m
unix:LIBS += -lqmmp -lqmmpui -lqjson -lPythonQt -lpython3 -lcurl

SOURCES += src/youtubewindow.cpp \
	src/youtubepreferences.cpp \
	src/youtubesearch.cpp \
	src/youtubevideostreams.cpp \
	src/youtubedl.cpp \
	src/youtube.cpp \
	src/youtubefactory.cpp \
	src/youtubeinputsource.cpp \
	src/youtubestreamreader.cpp

HEADERS += src/youtubewindow.h \
	src/youtubepreferences.h \
	src/youtubesearch.h \
	src/youtubevideostreams.h \
	src/youtubedl.h \
	src/youtube.h \
	src/youtubefactory.h \
	src/youtubeinputsource.h \
	src/youtubestreamreader.h


FORMS += src/youtubewindow.ui \
	src/youtubepreferences.ui

