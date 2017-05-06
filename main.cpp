#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Init resource here
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(graphio);
    MainWindow w;
    w.setGeometry(100, 100, 800, 500);
    w.show();

    return a.exec();
}
