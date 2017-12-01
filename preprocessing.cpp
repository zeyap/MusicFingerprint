#include <preprocessing.h>
#define Sample_Size 16
#define Sample_Rate 80//Hz
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

    const QString fname="20130505134926.mp3";
    if(QFile::exists(fname)){
        decoder->setSourceFilename(fname);
    }else{
        QMessageBox msgBox;
        msgBox.setText("No such file named "+fname);
        msgBox.exec();
    }

    connect(decoder, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));

    SamplePerFrame=Sample_Rate*Frame_Size;

    start();

}

void Preprocessing::start(){
    decoder->start();//startdecoding
    status=decoder->state();
    error=decoder->error();
}

void Preprocessing::readBuffer(){

    buffer=decoder->read();
    scount=buffer.sampleCount();
    std::vector<double> dataInDouble;
    if(buffer.format().sampleType()==QAudioFormat::SignedInt){
        QAudioBuffer::S16S * data=buffer.data<QAudioBuffer::S16S>();
        for(int i=0;i<scount;i++){
            dataInDouble.push_back(data[i].left);
        }
    }
    else if (buffer.format().sampleType() == QAudioFormat::UnSignedInt){
        QAudioBuffer::S16U *data = buffer.data<QAudioBuffer::S16U>();
        for(int i=0;i<scount;i++){
            dataInDouble.push_back(data[i].left);
        }
    }
    else if(buffer.format().sampleType() == QAudioFormat::Float){
        QAudioBuffer::S32F *data = buffer.data<QAudioBuffer::S32F>();
        for(int i=0;i<scount;i++){
            dataInDouble.push_back(data[i].left);
        }
    }
    bufferData(dataInDouble,scount);


    Framing(currentBuffer);

}

void Preprocessing::bufferData(std::vector<double> data, qint32 N){
    //std::vector<double> currentBuffer;
    for (int i = 0; i < N; i++){
        currentBuffer.push_back(data[i]);
    }
    //return currentBuffer;
}

void Preprocessing::onFinished(){
    QMessageBox msgBox;
    msgBox.setText("finished");
    msgBox.exec();

    readBuffer();

}

void Preprocessing::Framing(std::vector<double> buffer){
    int fcount=(scount-1)/SamplePerFrame;

    for(int fNum=0;fNum<fcount;fNum+=fcount){

        std::vector<double> frame;

        for(int i=0;i<SamplePerFrame;i++){

            int sIdx=fNum*SamplePerFrame+i;
            if(sIdx<scount){
                frame.push_back(buffer[sIdx]);
            }
        }
        int n=frame.size();

        newDFT=new LinearTrans(frame,n);
        delete(newDFT);

    }
}

