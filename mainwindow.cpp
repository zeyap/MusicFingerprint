#include "mainwindow.h"

MainWindow::MainWindow()
{
    preprocessing=new Preprocessing();
    recorder=new Recorder();
    renderArea=RenderArea::getInstance();

    readButton=new QPushButton(tr("read audio"));
    connect(readButton,SIGNAL(clicked(bool)),this,SLOT(Decode()));

    fileButton=new QPushButton(tr("file"));
    connect(fileButton,SIGNAL(clicked(bool)),this,SLOT(ChooseFile()));
    fileLabel=new QLabel(tr("Add a new song to library"));

    recordButton=new QPushButton(tr("start recording"));
    connect(recordButton,SIGNAL(clicked(bool)),this,SLOT(RecordSwitch()));

    searchButton=new QPushButton(tr("search"));
    connect(searchButton,SIGNAL(clicked(bool)),this,SLOT(StartSearch()));

    searchLabel=new QLabel(tr("[SEARCH YOUR MUSIC]"));

    updateButton=new QPushButton(tr("update library"));
    connect(updateButton,SIGNAL(clicked(bool)),this,SLOT(UpdateLibrary()));

    console = new QLabel(tr(""));
    connect(preprocessing,SIGNAL(SearchDone(QString)),this,SLOT(DisplaySearchResult(QString)));

    QGridLayout *mainLayout =new QGridLayout;

    mainLayout->addWidget(renderArea,0,0,1,4);
    mainLayout->addWidget(console,0,0,1,4,Qt::AlignCenter);

    mainLayout->addWidget(recordButton,1,1);
    mainLayout->addWidget(searchButton,1,2);
    mainLayout->addWidget(searchLabel,1,0,Qt::AlignRight);

    mainLayout->addWidget(readButton,2,2);
    mainLayout->addWidget(fileButton,2,1);
    mainLayout->addWidget(updateButton,2,3);
    mainLayout->addWidget(fileLabel,2,0,Qt::AlignRight);

    isRecording=false;
    EnableUpdate();

    setLayout(mainLayout);

    resize(600,300);
}

void MainWindow::Decode(){
    renderArea->Init();
    preprocessing->Decode(1);
    EnableUpdate();
}

void MainWindow::RecordSwitch(){
    if(isRecording==false){
        recorder->StartRecording();
        recordButton->setText("stop Recording");
    }else{
        recorder->StopRecording();
        recordButton->setText("start Recording");
        QString fname=recorder->getRecordingFileName();
        preprocessing->SetTargetFile(fname);
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

void MainWindow::StartSearch(){
    renderArea->Init();
    preprocessing->Decode(0);
}

void MainWindow::DisplaySearchResult(QString res){
    console->setText(res);
}

void MainWindow::UpdateLibrary(){
    if(isLibraryToBeUpdated){
        indexManager = new IndexManager();
        DisableUpdate();
    }
}

void MainWindow::EnableUpdate(){
    isLibraryToBeUpdated=true;
    updateButton->setText(tr("update library"));
}

void MainWindow::DisableUpdate(){
    isLibraryToBeUpdated=false;
    updateButton->setText(tr("library updated"));
}
