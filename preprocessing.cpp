#include <preprocessing.h>

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

    const QString fname="GOING_STEADY_BABY_BABY.mp3";
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
    totalscount=0;

    start();

}

void Preprocessing::start(){
    decoder->start();//startdecoding
    status=decoder->state();
    error=decoder->error();
}

void Preprocessing::readBuffer(){

    QAudioBuffer buffer=decoder->read();
    int scount=buffer.frameCount();
    //frame: one sample per channel for the same instant in time.
    //sample=frame*channel: the number of samples in this buffer
    totalscount+=scount;
    std::vector<double> bufferDataInDouble;
    if(buffer.format().sampleType()==QAudioFormat::SignedInt){
        const QAudioBuffer::S16S * data=buffer.constData<QAudioBuffer::S16S>();
        for(int i=0;i<scount;i++){
            bufferDataInDouble.push_back((double)data[i].average());
        }
    }
    else if (buffer.format().sampleType() == QAudioFormat::UnSignedInt){
        const QAudioBuffer::S16U *data = buffer.constData<QAudioBuffer::S16U>();
        for(int i=0;i<scount;i++){
            bufferDataInDouble.push_back(data[i].average());
        }
    }
    else if(buffer.format().sampleType() == QAudioFormat::Float){
        const QAudioBuffer::S32F *data = buffer.constData<QAudioBuffer::S32F>();
        for(int i=0;i<scount;i++){
            bufferDataInDouble.push_back(data[i].average());
        }
    }
    bufferData(bufferDataInDouble,scount);
}

void Preprocessing::bufferData(std::vector<double> data, qint32 N){
    for (int i = 0; i < N; i++){
        pcmBuffer.push_back(data[i]);
    }
}

void Preprocessing::onFinished(){
    QMessageBox msgBox;
    msgBox.setText("finished");
    msgBox.exec();

    Framing(pcmBuffer);
}

void Preprocessing::Framing(std::vector<double> pcmBuffer){
    int fcount=(totalscount-1)/SamplePerFrame;

    for(int fNum=0;fNum<fcount;fNum+=1){

        std::vector<double> frame;

        //getFrame from buffer
        for(int i=fNum*SamplePerFrame;i<(fNum+1)*SamplePerFrame;i++){
            if(i<totalscount){
                frame.push_back(pcmBuffer[i]);
            }
        }

        FrameProcess(frame,fNum);

    }
}

void Preprocessing::FrameProcess(std::vector<double> frame,int fnum){
    int n=frame.size();
    newDFT=new LinearTrans(frame,fnum);
    delete(newDFT);
}


