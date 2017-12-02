#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QGridLayout>
#include "preprocessing.h"
#include "renderarea.h"
#include <QPushButton>
#include<QLabel>
#include <QFileInfo>
#include<QFileDialog>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    //~MainWindow();
    Preprocessing* preprocessing;
private slots:
    void Decode();
    void ChooseFile();

private:
    RenderArea* renderArea;
    QPushButton* readButton;
    QPushButton* fileButton;
    QLabel* fileLabel;

};

#endif // MAINWINDOW_H
