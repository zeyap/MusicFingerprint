#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QGridLayout>
#include "preprocessing.h"
#include "renderarea.h"
#include <QPushButton>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    //~MainWindow();
    Preprocessing* preprocessing;
private slots:
    void Decode();

private:
    RenderArea* renderArea;
    QPushButton* readButton;
};

#endif // MAINWINDOW_H
