#include "mainwindow.h"

MainWindow::MainWindow()
{
    preprocessing=new Preprocessing();
    recorder=new Recorder();
    indexManager = new IndexManager();
    renderArea=RenderArea::getInstance();

    readButton=new QPushButton(tr("read audio"));
    connect(readButton,SIGNAL(clicked(bool)),this,SLOT(Decode()));

    fileButton=new QPushButton(tr("file"));
    connect(fileButton,SIGNAL(clicked(bool)),this,SLOT(ChooseFile()));
    fileLabel=new QLabel(tr("Add a new song to library"));

    recordButton=new QPushButton(tr("start recording"));
    connect(recordButton,SIGNAL(clicked(bool)),this,SLOT(RecordSwitch()));

    searchButton=new QPushButton(tr("search"));
    connect(searchButton,SIGNAL(clicked(bool)),this,SLOT(Search()));

    searchLabel=new QLabel(tr("[SEARCH YOUR MUSIC]"));

    QGridLayout *mainLayout =new QGridLayout;

    mainLayout->addWidget(renderArea,0,0,1,3);

    mainLayout->addWidget(recordButton,1,1);
    mainLayout->addWidget(searchButton,1,2);
    mainLayout->addWidget(searchLabel,1,0,Qt::AlignRight);

    mainLayout->addWidget(readButton,2,2);
    mainLayout->addWidget(fileButton,2,1);
    mainLayout->addWidget(fileLabel,2,0,Qt::AlignRight);

    isRecording=false;

    setLayout(mainLayout);

    resize(500,300);
}

void MainWindow::Decode(){
    renderArea->Init();
    preprocessing->Decode();
}

void MainWindow::RecordSwitch(){
    if(isRecording==false){
        recorder->StartRecording();
        recordButton->setText("stop Recording");
    }else{
        recorder->StopRecording();
        recordButton->setText("start Recording");
        QString fname=recorder->getRecordingFileName();
    }
    isRecording=!isRecording;
}

void MainWindow::ChooseFile(){
    QString file_full,file_path,file_name;
    QFileInfo fi;
    file_full=QFileDialog::getOpenFileName(this);
    fi=QFileInfo(file_full);
    //file_path=fi.absolutePath();
    file_path=fi.fileName();
    file_name=fi.fileName();
    fileLabel->setText(file_name);
    preprocessing->SetTargetFile(file_path);
}

void MainWindow::Search(){

}
