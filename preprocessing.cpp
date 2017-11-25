#include <preprocessing.h>

Preprocessing::Preprocessing()
{
    decoder=new QAudioDecoder();
}

void Preprocessing::InitDecoder(){

    QAudioFormat format;
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setSampleRate(8000);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);

    decoder->setAudioFormat(format);

    const QString fname="201305051349262.mp3";
    if(QFile::exists(fname)){
        decoder->setSourceFilename(fname);
    }else{
        QMessageBox msgBox;
        msgBox.setText("No such file named "+fname);
        msgBox.exec();
    }

    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
    connect(decoder, SIGNAL(finished()), this, SLOT(onFinished()));

    start();

}

void Preprocessing::start(){
    decoder->start();//startdecoding
    status=decoder->state();
    error=decoder->error();
}

void Preprocessing::readBuffer(){
    buffer=decoder->read();
    data=buffer.constData<quint16>();
}

void Preprocessing::onFinished(){
    QMessageBox msgBox;
    msgBox.setText("finished");
    msgBox.exec();
}
