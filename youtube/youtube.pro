#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T04:29:04
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = youtube
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += /usr/include/python3.6m
unix:LIBS += -lqmmp -lqmmpui -lqjson -lPythonQt -lcurl

CONFIG += hide_symbols

SOURCES += \
    youtubefactory.cpp \
    youtubeinputsource.cpp \
    youtubestreamreader.cpp \
    youtubedl.cpp \
    youtubeapi.cpp

HEADERS += \
    youtubefactory.h \
    youtubeinputsource.h \
    youtubestreamreader.h \
    youtubedl.h \
    youtubeapi.h
