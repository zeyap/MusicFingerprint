#include <preprocessing.h>
#define Sample_Size 16
#define Sample_Rate 8000//Hz
#define Channel_Count 1
#define Frame_Size 0.1f//10-500 ms
#define Overlap 0.5f

Preprocessing::Preprocessing()
{
    decoder=new QAudioDecoder();
}

void Preprocessing::InitDecoder(){

    QAudioFormat format;
    format.setChannelCount(Channel_Count);
    format.setSampleSize(Sample_Size);
    format.setSampleRate(Sample_Rate);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);

    decoder->setAudioFormat(format);

    const QString fname="record.wav";
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

void Preprocessing::onFinished(){
    QMessageBox msgBox;
    msgBox.setText("finished");
    msgBox.exec();
}

void Preprocessing::readBuffer(){
    buffer=decoder->read();
    fcount=buffer.frameCount();
    QAudioBuffer::S16S * data;

    if(buffer.format().sampleType()==QAudioFormat::SignedInt){
        data=buffer.data<QAudioBuffer::S16S>();
        currentBuffer=bufferData(data,buffer.frameCount());
    }
    else if (buffer.format().sampleType() == QAudioFormat::UnSignedInt){

        QAudioBuffer::S16U *data = buffer.data<QAudioBuffer::S16U>();
        currentBuffer1=bufferData(data,buffer.frameCount());

    }
    else if(buffer.format().sampleType() == QAudioFormat::Float){

        QAudioBuffer::S32F *data = buffer.data<QAudioBuffer::S32F>();
        currentBuffer2=bufferData(data,buffer.frameCount());

    }

}

template<typename T>
std::vector<T> Preprocessing::bufferData(T *data, qint32 N){
    std::vector<T> currentBuffer;
    for (qint32 i = 0; i < N; i++){
        currentBuffer.push_back(data[i]);
    }
    return currentBuffer;
}

template<typename T>
void Preprocessing::Framing(std::vector<T> buffer,int start,int end){
    int SamplePerFrame=Sample_Rate*Frame_Size;
    std::vector<T> frame;
    for(int i=0;i<SamplePerFrame;i++){

    }
}

