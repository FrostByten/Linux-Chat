#include "mainwindow.h"
#include "clientsend.h"
#include "clientreceive.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();

    return a.exec();
}
