#include "mainwindow.h"
//#include "graphics/simplemainwindow.hh"
//#include "graphics/simpleactoritem.hh"

#include <QApplication>
//using namespace Ui;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    MainWindow main_window;
    main_window.show();

    return a.exec();
}
