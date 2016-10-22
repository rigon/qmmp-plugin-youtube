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

SOURCES += \
    youtubedl.cpp \
    youtubefactory.cpp \
    youtubeinputsource.cpp \
    youtubestreamreader.cpp \
    youtubeapi.cpp

HEADERS += \
    youtubedl.h \
    youtubefactory.h \
    youtubeinputsource.h \
    youtubestreamreader.h \
    youtubeapi.h

FORMS +=

