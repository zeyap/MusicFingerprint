#include "mainwindowMF.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindowMF w;
    w.show();

    return app.exec();
}
