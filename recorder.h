#ifndef RECORDER_H
#define RECORDER_H

#include "preprocessing.h"

class Recorder:public Preprocessing
{
public:
    Recorder();
    void StopRecording();
    void StartRecording();
    QString getRecordingFileName();

private:
    QFile* outputFile;
    QAudioInput* audio;
    int serial;
    QAudioFormat format;

    QString fpathPrefix="audioSource/newRecording";
    QString fpathSuffix=".raw";

};

#endif // RECORDER_H
