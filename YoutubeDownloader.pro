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
unix:LIBS += -lqmmp	-lqmmpui -lqjson -lPythonQt -lpython3.5m

SOURCES += main.cpp\
	youtubewindow.cpp \
	youtubepreferences.cpp \
	youtubesearch.cpp \
	youtubevideostreams.cpp \
	youtubedl.cpp \
	youtube.cpp \
	youtubefactory.cpp

HEADERS += youtubewindow.h \
	youtubepreferences.h \
	youtubesearch.h \
	youtubevideostreams.h \
	youtubedl.h \
	youtube.h \
	youtubefactory.h

FORMS += youtubewindow.ui \
	youtubepreferences.ui
