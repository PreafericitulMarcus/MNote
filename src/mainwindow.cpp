#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>
#include <QKeyEvent>

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
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_J), this, SLOT(allignLeft()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_K), this, SLOT(allignMiddle()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_L), this, SLOT(allignRight()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this, SLOT(undo()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_T), this, SLOT(uploadTemplate()));     new window needed
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_P), this, SLOT(printDocument()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this, SLOT(openDocument()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this, SLOT(newDocument()));
    // new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this, SLOT(findInDocument()));     new window needed
    new QShortcut(QKeySequence(Qt::SHIFT | Qt::Key_Enter), this, SLOT(jumpBelow()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Enter), this, SLOT(jumpAbove()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_L), this, SLOT(jumpEndLine()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_K), this, SLOT(deleteCurrentLine()));
}

void MainWindow::quit()
{
    QCoreApplication::quit();
}

void MainWindow::allignLeft()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::allignMiddle()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignHCenter);
    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::allignRight()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
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
    /*
       This function takes the position of the cursor in the textEdit,
       moves it to the END of the current line, and inserts a new block
       (which is like a new line). Then it sets the cursor to the new block.
    */

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.insertBlock();
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::jumpAbove()
{
    /*
       This function takes the position of the cursor in the textEdit,
       moves it to the START of the current line, and inserts a new block
       (which is like a new line). Then we move the cursor above the current line, to the new block.
       Then it sets the cursor to the new block.
    */
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.insertBlock();
    cursor.movePosition(QTextCursor::PreviousBlock);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::jumpEndLine()
{
    /*
       This function takes the position of the cursor in the textEdit,
       moves it to the END of the current line, and sets the cursor to that position.
    */
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::EndOfLine);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::deleteCurrentLine()
{
    /*
       This function takes the position of the cursor in the textEdit,
       moves it to the start of the current line, selects the entire line,
       and removes the selected text, effectively deleting the current line.
       The cursor is then set to the position at the start of the line.
    */
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    ui->textEdit->setTextCursor(cursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}
