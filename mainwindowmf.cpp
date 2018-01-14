#include "mainwindowmf.h"
#include "ui_mainwindowmf.h"

MainWindowMF::MainWindowMF(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowMF)
{
    preprocessing=new Preprocessing();
    recorder=new Recorder();
    renderArea=new RenderArea(this);
    renderArea->setFixedSize(500,500);

    connect(preprocessing,SIGNAL(SearchDone(QString)),this,SLOT(DisplaySearchResult(QString)));
    connect(preprocessing,SIGNAL(UpdateTag(std::vector<int>)),this,SLOT(UpdateTag(std::vector<int>)));
    connect(preprocessing,SIGNAL(DecodeFinish()),this,SLOT(OnDecodeFinish()));

    //ui->pushButton->setStyleSheet("color:red");
    ui->setupUi(this);

    isRecording=false;
    isImported=false;
    isLibraryToBeUpdated=true;
    EnableUpdate();
}

MainWindowMF::~MainWindowMF()
{
    delete ui;
}
void MainWindowMF::Decode(){
    renderArea->Init();
    preprocessing->Decode(1);
    EnableUpdate();
}
void MainWindowMF::RecordSwitch(){

    if(isRecording==false){
        recorder->StartRecording();
        ui->pushButton->setText("Click to search");
    }else{
        recorder->StopRecording();
        ui->pushButton->setText("Click and record");
        QString fname=recorder->getRecordingFileName();
        preprocessing->SetTargetFile(fname);
        StartSearch();
    }

    isRecording=!isRecording;
}
void MainWindowMF::ChooseFile(){
    QString file_full,file_path,file_name;
    QFileInfo fi;
    file_full=QFileDialog::getOpenFileName(this);
    fi=QFileInfo(file_full);
    //file_path=fi.absolutePath();
    file_path=fi.fileName();
    file_name=fi.fileName();
    ui->fileLabel->setText(file_name);
    preprocessing->SetTargetFile(file_path);
}

void MainWindowMF::DisplaySearchResult(QString res){
    QMessageBox msgBox;
    msgBox.setText(res);
    msgBox.exec();
}
void MainWindowMF::UpdateLibrary(){
    if(isLibraryToBeUpdated){
        ui->pushButton_5->setText(tr("Updating library..."));
        indexManager = new IndexManager();
        DisableUpdate();
    }
}
void MainWindowMF::StartSearch(){
    renderArea->Init();
    preprocessing->Decode(0);
}
void MainWindowMF::EnableUpdate(){
    isLibraryToBeUpdated=true;
    ui->pushButton_5->setText(tr("Update library"));
}

void MainWindowMF::DisableUpdate(){
    isLibraryToBeUpdated=false;
    ui->pushButton_5->setText(tr("Library up to date"));
}

void MainWindowMF::UpdateTag(std::vector<int> newTag){
    renderArea->GetTag(newTag);
}

//record or search
void MainWindowMF::on_pushButton_clicked()
{
    RecordSwitch();
}

//file
void MainWindowMF::on_pushButton_3_clicked()
{
    if(isImported==false){
        ChooseFile();
        isImported=true;
        ui->pushButton_3->setText(tr("Click to decode"));
    }else{
        Decode();
        isImported=false;
        ui->pushButton_3->setText(tr("Decoding music..."));
    }

}

void MainWindowMF::OnDecodeFinish(){
    ui->pushButton_3->setText(tr("Import local music"));
}

//update
void MainWindowMF::on_pushButton_5_clicked()
{
    UpdateLibrary();
}
