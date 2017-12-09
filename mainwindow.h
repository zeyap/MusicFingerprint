#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QGridLayout>
#include <QPushButton>
#include<QLabel>
#include <QFileInfo>
#include<QFileDialog>

#include "preprocessing.h"
#include "recorder.h"
#include "renderarea.h"
#include "indexmanager.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    //~MainWindow();
    Preprocessing* preprocessing;
    Recorder* recorder;
    IndexManager* indexManager;
private slots:
    void Decode();
    void RecordSwitch();
    void ChooseFile();
    void StartSearch();

private:
    RenderArea* renderArea;

    QPushButton* readButton;

    QPushButton* fileButton;
    QLabel* fileLabel;

    QPushButton* recordButton;
    QPushButton* searchButton;
    QLabel* searchLabel;
    bool isRecording;

};

#endif // MAINWINDOW_H
