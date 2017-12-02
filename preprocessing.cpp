#include <preprocessing.h>

Preprocessing::Preprocessing()
{
    decoder=new QAudioDecoder();
    fpath="default.mp3";
    InitDecoder();
}

void Preprocessing::InitDecoder(){

    QAudioFormat format;
    format.setChannelCount(Channel_Count);
    format.setSampleSize(Sample_Size);
    format.setSampleRate(Sample_Rate);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);

    decoder->setAudioFormat(format);

    connect(decoder, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));

    SamplePerFrame=Sample_Rate*Frame_Size;
    FrameSampleOffset=Frame_Interval*Sample_Rate;

}

void Preprocessing::Decode(){

    totalscount=0;

    ClearBuffers();

    if(QFile::exists(fpath)){
        decoder->setSourceFilename(fpath);
        start();
    }else{
        QMessageBox msgBox;
        msgBox.setText("No such file named "+fpath);
        msgBox.exec();
    }

}

void Preprocessing::ClearBuffers(){
    while(pcmBuffer.size()>0){
        pcmBuffer.pop_back();
    }
    while(featureBuffer.size()>0){
        featureBuffer.pop_back();
    }
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

    OutputFeatureBuffer();
}

void Preprocessing::Framing(std::vector<double> pcmBuffer){
    int fcount=(totalscount-SamplePerFrame)/FrameSampleOffset+1;//(totalscount-1)/SamplePerFrame;

    for(int fNum=0;fNum<fcount;fNum+=1){

        std::vector<double> frame;

        //getFrame from buffer
        for(int i=fNum*FrameSampleOffset;i<fNum*FrameSampleOffset+SamplePerFrame;i++){
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

    FrameFeature newf;
    newf.f=newDFT->GetFeatureVector();
    newf.t=fnum*Frame_Interval;

    featureBuffer.push_back(newf);

    delete(newDFT);
}

void Preprocessing::SetTargetFile(QString newfpath){
    fpath=newfpath;
}

void Preprocessing::OutputFeatureBuffer(){
    QString filename="featureOutput/"+fpath+".csv";
    QFile file(filename);
    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &file );
        stream << "sample size (bit), " << Sample_Size<<", ";
        stream << "sample rate (Hz), "<<Sample_Rate<<", ";
        stream << "frame size (sec), "<< Frame_Size<<", ";
        stream << "frame interval(sec), "<<Frame_Interval;
        stream<<"\n";
        int buffersz=featureBuffer.size();
        int featuresz=featureBuffer[0].f.size();
        for(int i=0;i<buffersz;i++){
            for(int j=0;j<featuresz;j++){
                stream << featureBuffer[i].f[j]<<", ";
            }
            stream << featureBuffer[i].t <<", " ;
            stream << fpath;
            stream<<"\n";
        }

    }
}
