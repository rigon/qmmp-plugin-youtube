include(../../plugins.pri)
HEADERS += \
    youtubeinputfactory.h \
    youtubeinputsource.h \
    settingsdialog.h \
    youtubestreamreader.h
SOURCES += \
    youtubeinputfactory.cpp \
    youtubeinputsource.cpp \
    settingsdialog.cpp \
    youtubestreamreader.cpp
win32:HEADERS += ../../../../src/qmmp/inputsource.h \
    ../../../../src/qmmp/inputsourcefactory.h
TARGET = $$PLUGINS_PREFIX/Transports/youtube
unix:QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libyoutube.so
INCLUDEPATH += ../../../
CONFIG += warn_on \
    plugin \
    link_pkgconfig
TEMPLATE = lib
unix { 
    QMAKE_LIBDIR += ../../../../lib
    LIBS += -lqmmp \
        -L/usr/lib
    PKGCONFIG += libcurl
    isEmpty(LIB_DIR):LIB_DIR = /lib
    target.path = $$LIB_DIR/qmmp/Transports
    INSTALLS += target
}
win32 { 
    QMAKE_LIBDIR += ../../../../bin
    LIBS += -lqmmp0 \
        -lcurldll
}

contains(CONFIG, WITH_ENCA){
   CONFIG += link_pkgconfig
   DEFINES += WITH_ENCA
   unix:PKGCONFIG += enca
   win32:LIBS += -lenca.dll

}

FORMS += settingsdialog.ui

TRANSLATIONS = translations/youtube_plugin_ru.ts \
    translations/youtube_plugin_uk_UA.ts \
    translations/youtube_plugin_zh_CN.ts \
    translations/youtube_plugin_zh_TW.ts \
    translations/youtube_plugin_cs.ts \
    translations/youtube_plugin_pl.ts \
    translations/youtube_plugin_de.ts \
    translations/youtube_plugin_it.ts \
    translations/youtube_plugin_tr.ts \
    translations/youtube_plugin_lt.ts \
    translations/youtube_plugin_nl.ts \
    translations/youtube_plugin_ja.ts \
    translations/youtube_plugin_es.ts \
    translations/youtube_plugin_sr_BA.ts \
    translations/youtube_plugin_sr_RS.ts

RESOURCES = translations/translations.qrc
