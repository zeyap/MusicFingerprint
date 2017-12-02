#include "recorder.h"

Recorder::Recorder()
{
    serial=0;
    format=getFormat();
    //cout <<"record begin!" << endl;

}

QString Recorder::getRecordingFileName(){
    return "newRecording"+QString::number(serial,10)+fpathSuffix;
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
}
