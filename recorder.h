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

    struct WavFileHeader
    {
        // RIFF header
        char riffName[4];//file Id
        unsigned long riffLength;//file length

        char wavName[4];//wave Id

        // format chunk - header
        char fmtName[4];//chunk Id
        unsigned long fmtLength;//chunk length

        // format chunk - data
        unsigned short audioFormat;
        unsigned short channleNumber;
        unsigned long sampleRate;
        unsigned long bytesPerSecond;
        unsigned short bytesPerSample;
        unsigned short bitsPerSample;

        // data chunk - header
        char    dataName[4];
        unsigned long   dataLength;

        // data chunk - data
        // ...
    };

    int AddWavHeader();

};

#endif // RECORDER_H
