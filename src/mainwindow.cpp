#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QShortcut>
#include <QKeyEvent>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    this->setWindowTitle("MNote");
    ui->setupUi(this);

    setupKeyboardShortcuts();
    // Install event filter on textEdit for Ctrl+Enter
    ui->textEdit->installEventFilter(this);
}

void MainWindow::setupKeyboardShortcuts()
{
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(save()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_V), this, SLOT(paste()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q), this, SLOT(quit()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_J), this, SLOT(indentLeft()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_K), this, SLOT(indentMiddle()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_L), this, SLOT(indentRight()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this, SLOT(undo()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_T), this, SLOT(uploadTemplate()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_P), this, SLOT(printDocument()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this, SLOT(openDocument()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this, SLOT(newDocument()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this, SLOT(findInDocument()));
    new QShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Enter), this, SLOT(jumpBelow()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Enter), this, SLOT(jumpAbove()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_L), this, SLOT(jumpEndLine()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Shift | Qt::Key_K), this, SLOT(deleteCurrentLine()));
}

void MainWindow::quit()
{
    QCoreApplication::quit();
}

// eventFilter catches textEdit ui object and the Ctrl+Enter key combination event
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->textEdit && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        // Ctrl+Enter (or Ctrl+Return)
        if ((keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) &&
            (keyEvent->modifiers() & Qt::ControlModifier) &&
            !(keyEvent->modifiers() & Qt::ShiftModifier))
        {
            jumpBelow();
            return true;
        }
        // Ctrl+Shift+Enter (or Ctrl+Shift+Return)
        if ((keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) &&
            (keyEvent->modifiers() & Qt::ControlModifier) &&
            (keyEvent->modifiers() & Qt::ShiftModifier))
        {
            jumpAbove();
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::jumpBelow()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertBlock();
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::jumpAbove()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::PreviousBlock);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::jumpEndLine()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::EndOfLine);
    ui->textEdit->setTextCursor(cursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}
