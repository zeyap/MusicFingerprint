QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH+= \fftw3

LIBS+=D:\Study\VideoAudio_Processing\musicprocessing\mf\MusicFingerprint\fftw3\libfftw3-3.lib
LIBS+=D:\Study\VideoAudio_Processing\musicprocessing\mf\MusicFingerprint\fftw3\libfftw3f-3.lib
LIBS+=D:\Study\VideoAudio_Processing\musicprocessing\mf\MusicFingerprint\fftw3\libfftw3l-3.lib

TARGET = MusicFingerprint

SOURCES += \
        main.cpp \
    preprocessing.cpp \
    lineartrans.cpp \
    renderarea.cpp \
    recorder.cpp \
    indexmanager.cpp \
    search.cpp \
    mainwindowmf.cpp

HEADERS += \
    preprocessing.h \
    lineartrans.h \
    renderarea.h \
    main.h \
    recorder.h \
    indexmanager.h \
    search.h \
    mainwindowmf.h

FORMS += \
    mainwindowmf.ui

RESOURCES += \
    MusicFingerprint.qrc
