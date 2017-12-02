#include "mainwindow.h"

MainWindow::MainWindow()
{
    preprocessing=new Preprocessing();
    renderArea=RenderArea::getInstance();

    readButton=new QPushButton(tr("read audio"));
    connect(readButton,SIGNAL(clicked(bool)),this,SLOT(Decode()));

    //scrollBar = new QScrollBar(Qt::Horizontal);

    QGridLayout *mainLayout =new QGridLayout;

    mainLayout->addWidget(renderArea);
    mainLayout->addWidget(readButton,1,0);
    //mainLayout->addWidget(scrollBar,2,0);
    setLayout(mainLayout);

    resize(1000,600);

    //connect(scrollBar,SIGNAL(valueChanged(int)),renderArea,SLOT(Move(int)));

}

void MainWindow::Decode(){
    preprocessing->InitDecoder();
}

