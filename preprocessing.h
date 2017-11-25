#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <QMultimedia>
#include <QAudioFormat>
#include <QAudioDecoder>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QWidget>

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
    const quint16 * data;

    int status,error;
    void start();


};

#endif // PREPROCESSING_H
