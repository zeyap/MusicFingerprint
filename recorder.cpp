#include "recorder.h"

Recorder::Recorder()
{
    serial=0;
    format=getFormat();
    //cout <<"record begin!" << endl;

}

QString Recorder::getRecordingFileName(){
    return "newRecording"+QString::number(serial,10)+".wav";
}

void Recorder::StartRecording(){

    while(QFile::exists(fpathPrefix+QString::number(serial,10)+fpathSuffix)){
        serial++;
    }
    outputFile=new QFile;
    outputFile->setFileName(fpathPrefix+QString::number(serial,10)+fpathSuffix);
    if(!outputFile->open( QIODevice::WriteOnly | QIODevice::Truncate )){
        return;
    }
    audio = new QAudioInput(format, this);
    audio->start(outputFile);
}

void Recorder::StopRecording(){
    audio->stop();
    outputFile->close();
    delete outputFile;
    delete audio;
    //cout <<"record end!" << endl;
    if(AddWavHeader()<0){
        QMessageBox msgBox;
        msgBox.setText("error when saving .wav file.");
        msgBox.exec();
    }
}

int Recorder::AddWavHeader(){
    WavFileHeader wavFileHeader;
    qstrcpy(wavFileHeader.riffName,"RIFF");
    qstrcpy(wavFileHeader.wavName,"WAVE");
    qstrcpy(wavFileHeader.fmtName,"fmt ");

    wavFileHeader.fmtLength=16;
    wavFileHeader.audioFormat=1;

    qstrcpy(wavFileHeader.dataName,"data");

    wavFileHeader.bitsPerSample=Sample_Size;
    wavFileHeader.bytesPerSample=2;
    wavFileHeader.sampleRate=Sample_Rate;
    wavFileHeader.bytesPerSecond=Sample_Rate*2;
    wavFileHeader.channleNumber=Channel_Count;

    QString cacheFileName=fpathPrefix+QString::number(serial,10)+fpathSuffix;
    QString wavFileName=fpathPrefix+QString::number(serial,10)+".wav";
    QFile cacheFile(cacheFileName);
    QFile wavFile(wavFileName);

    if(!cacheFile.open(QIODevice::ReadWrite)){
        return -1;
    }
    if(!wavFile.open(QIODevice::WriteOnly)){
        return -2;
    }

    int headerSize=sizeof(wavFileHeader);
    qint64 fileLen=cacheFile.bytesAvailable();

    wavFileHeader.riffLength=fileLen-8+headerSize;
    wavFileHeader.dataLength=fileLen;

    wavFile.write((char*) &wavFileHeader,headerSize);
    wavFile.write(cacheFile.readAll());

    wavFile.close();

    return fileLen;
}







