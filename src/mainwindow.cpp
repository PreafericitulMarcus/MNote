#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("MNote");
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked, this, &MainWindow::display);
}


void MainWindow::display()
{
    qDebug() << ui->textEdit->toPlainText();
}

MainWindow::~MainWindow()
{
    delete ui;
}
