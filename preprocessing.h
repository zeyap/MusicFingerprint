#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <main.h>

#include <QMultimedia>
#include <QAudioFormat>
#include <QAudioDecoder>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QWidget>
#include <iostream>
#include <vector>
#include <lineartrans.h>

class Preprocessing : public QWidget
{
    Q_OBJECT

public:
    Preprocessing();
    void SetTargetFile(QString newfpath);
public slots:
    void Decode();
private slots:
    void readBuffer();
    void onFinished();
    void InitDecoder();

private:
    QAudioDecoder* decoder;
    int totalscount;
    int SamplePerFrame;

    QString fpath;

    int status,error;
    void start();

    void ClearPCMBuffer();

    void bufferData(std::vector<double> data, qint32 N);
    void Framing(std::vector<double> pcmBuffer);
    void FrameProcess(std::vector<double> frame, int fnum);

    std::vector<double> pcmBuffer;

    LinearTrans* newDFT;

};

#endif // PREPROCESSING_H
