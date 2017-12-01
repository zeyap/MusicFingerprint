#include "mainwindow.h"

MainWindow::MainWindow()
{
    preprocessing=new Preprocessing();
    renderArea=new RenderArea;

    readButton=new QPushButton(tr("read audio"));
    connect(readButton,SIGNAL(clicked(bool)),this,SLOT(Decode()));

    QGridLayout *mainLayout =new QGridLayout;

    mainLayout->setRowStretch(0,renderArea->height);
    resize(800,600);
    mainLayout->addWidget(renderArea,0,0,renderArea->height,renderArea->width);
    mainLayout->addWidget(readButton,1,0);
    setLayout(mainLayout);
}

void MainWindow::Decode(){
    preprocessing->InitDecoder();
}

