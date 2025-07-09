#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("MNote");

    // added the conslas font and some validation. 
    int fontId = QFontDatabase::addApplicationFont(":/fonts/YaHei.Consolas.1.12.ttf");
    if (fontId < 0)
        qDebug() << "Failed to load Consolas font";
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont consolas(family);
    QApplication::setFont(consolas);    

    MainWindow window;
    window.resize(800, 450);
    window.show();

    return app.exec();
}
