#include "mainwindow.h"

#include <QApplication> 

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QApplication::setApplicationName("MNote");
    // ? TODO: Add font maybe ? addApplicationFont <- consolas ?

    MainWindow window;
    window.show();
    
    return app.exec();
}
