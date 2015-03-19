include(../../../qmmp.pri)

SUBDIRS += http \
           youtube

unix:SUBDIRS += mms
TEMPLATE = subdirs
