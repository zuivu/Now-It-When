QT += testlib
QT -= gui

TARGET = tst_statistictest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_statisticstest.cpp \
    ../../Game/statistics.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../Course/CourseLib/interfaces/istatistics.hh \
    ../../Game/statistics.h

INCLUDEPATH += \
            ../../Game/ \
            ../../Course/CourseLib

DEPENDPATH += \
            ../../Game/ \
            ../../Course/CourseLib
