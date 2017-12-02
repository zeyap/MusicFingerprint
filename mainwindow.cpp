#include "mainwindow.h"

MainWindow::MainWindow()
{
    preprocessing=new Preprocessing();
    renderArea=RenderArea::getInstance();

    readButton=new QPushButton(tr("read audio"));
    connect(readButton,SIGNAL(clicked(bool)),this,SLOT(Decode()));

    fileButton=new QPushButton(tr("file"));
    connect(fileButton,SIGNAL(clicked(bool)),this,SLOT(ChooseFile()));

    fileLabel=new QLabel(tr("Choose a file."));

    QGridLayout *mainLayout =new QGridLayout;

    mainLayout->addWidget(renderArea,0,0,1,3);
    mainLayout->addWidget(readButton,1,2);
    mainLayout->addWidget(fileButton,1,1);
    mainLayout->addWidget(fileLabel,1,0,Qt::AlignRight);
    setLayout(mainLayout);

    resize(1000,600);
}

void MainWindow::Decode(){
    renderArea->Init();
    preprocessing->Decode();
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

