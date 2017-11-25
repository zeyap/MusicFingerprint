#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    preprocessing=new Preprocessing();
    connect(ui->readButton,SIGNAL(clicked(bool)),this,SLOT(Decode()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Decode(){
    preprocessing->InitDecoder();
}

