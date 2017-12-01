#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#define Sample_Size 16
#define Sample_Rate 80//Hz
#define Channel_Count 1
#define Frame_Size 0.1f//10-500 ms
#define Overlap 0.5f

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
public slots:
    void InitDecoder();
private slots:
    void readBuffer();
    void onFinished();

private:
    QAudioDecoder* decoder;
    int totalscount;
    int SamplePerFrame;

    int status,error;
    void start();

    void bufferData(std::vector<double> data, qint32 N);
    void Framing(std::vector<double> sBuffer);
    void FrameProcess(std::vector<double> frame);

    std::vector<double> currentBuffer;

    LinearTrans* newDFT;

};

#endif // PREPROCESSING_H
