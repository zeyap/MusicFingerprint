#ifndef PREPROCESSING_H
#define PREPROCESSING_H

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
    QAudioBuffer buffer;
    int scount;
    int SamplePerFrame;

    int status,error;
    void start();

    void bufferData(std::vector<double> data, qint32 N);
    void Framing(std::vector<double> buffer);

    std::vector<double> currentBuffer;

    lineartrans* newDFT;

};

#endif // PREPROCESSING_H
