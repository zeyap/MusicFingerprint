#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "preprocessing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Preprocessing* preprocessing;
private slots:
    void Decode();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
