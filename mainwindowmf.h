#ifndef MAINWINDOWMF_H
#define MAINWINDOWMF_H


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
namespace Ui {
class MainWindowMF;
}

class MainWindowMF : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowMF(QWidget *parent = 0);
    ~MainWindowMF();
    Preprocessing* preprocessing;
    Recorder* recorder;
    IndexManager* indexManager;
    RenderArea* renderArea;

private slots:
    void Decode();
    void RecordSwitch();
    void ChooseFile();
    void StartSearch();
    void UpdateLibrary();
    void DisplaySearchResult(QString res);
    void UpdateTag(std::vector<int> newTag);
    void OnDecodeFinish();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();


private:
    Ui::MainWindowMF *ui;
    void DisableUpdate();
    void EnableUpdate();
    QLabel* fileLabel;
    bool isRecording;
    bool isImported;
    bool isLibraryToBeUpdated;

};

#endif // MAINWINDOWMF_H
