QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicFingerprint

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    preprocessing.cpp

HEADERS += \
        mainwindow.h \
    preprocessing.h

FORMS += \
        mainwindow.ui
