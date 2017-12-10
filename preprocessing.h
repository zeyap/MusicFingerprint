#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <main.h>

#include <QMultimedia>
#include <QAudioFormat>
#include <QAudioDecoder>
#include <QObject>
#include <QMessageBox>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QAudioInput>
#include <iostream>
#include <vector>
#include <lineartrans.h>
#include <indexmanager.h>

class Preprocessing : public QWidget
{
    Q_OBJECT

public:
    Preprocessing();
    void SetTargetFile(QString newfpath);
    QAudioFormat getFormat();

public slots:
    void Decode(int newAudioType);

signals:
    void SearchDone(QString res);

private slots:
    void readBuffer();
    void onFinished();
    void InitDecoder();

private:
    QAudioDecoder* decoder;
    int totalscount;
    int SamplePerFrame;
    int FrameSampleOffset;

    QString fpath;
    QString fpathPrefix;

    int status,error;
    void start();

    void ClearBuffers();

    void bufferData(std::vector<double> data, qint32 N);
    void Framing(std::vector<double> pcmBuffer);
    void FrameProcess(std::vector<double> frame, int fnum);

    void OutputFeatureBuffer();

    std::vector<double> pcmBuffer;

    std::vector<FrameFeature> featureBuffer;

    int audioType;//0 record, 1 full-music

};

#endif // PREPROCESSING_H
