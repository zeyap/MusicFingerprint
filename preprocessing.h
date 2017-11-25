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
    int fcount;

    int status,error;
    void start();

    template<typename T>
    std::vector<T> bufferData(T *data, qint32 N);

    template<typename T>
    void Framing(std::vector<T> buffer,int start,int end);

    std::vector<QAudioBuffer::S16S> currentBuffer;
    std::vector<QAudioBuffer::S16U> currentBuffer1;
    std::vector<QAudioBuffer::S32F> currentBuffer2;


};

#endif // PREPROCESSING_H
