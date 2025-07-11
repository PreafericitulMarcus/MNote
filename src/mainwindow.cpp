#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>
#include <QKeyEvent>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QLabel>
#include <QStatusBar>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    this->setWindowTitle("MNote");
    ui->setupUi(this);

    setupKeyboardShortcuts();
    // Install event filter on textEdit for Ctrl+Enter
    ui->textEdit->installEventFilter(this);

    // Autosave timer setup
    autosaveTimer = new QTimer(this);
    connect(autosaveTimer, &QTimer::timeout, this, &MainWindow::save);

    // Setup status bar
    setupStatusBar();

    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::updateWordCount);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::updateSaveStatus);

    // Initial word count update
    updateWordCount();
}

void MainWindow::setupStatusBar()
{
    // Initialize status bar labels. word count and save status
    wordCountLabel = new QLabel(this);
    saveLabel = new QLabel(this);
    statusBar()->setStyleSheet("min-height: 17px; max-height: 17px; padding: 0; margin: 0;");
    statusBar()->addPermanentWidget(wordCountLabel);
    statusBar()->addWidget(saveLabel);
    wordCountLabel->setStyleSheet("padding-right: 8px; font-size: 12px; qproperty-alignment: AlignCenter;");
    saveLabel->setStyleSheet("color: #EA3C53; padding-left: 5px; font-size: 12px; qproperty-alignment: AlignCenter;");
    saveLabel->setText("NOT SAVED"); // Initial text for save label
}

void MainWindow::setupKeyboardShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(save()));
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

void MainWindow::updateWordCount()
{
    // Count words in the textEdit
    QString text = ui->textEdit->toPlainText();

    // Use a regular expression to split the text by whitespace and count the words.
    // At first it is 0, then update.
    int wordCount = text.isEmpty() ? 0 : text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).count();

    // Update the word count label in the status bar
    wordCountLabel->setText(QString("w:%1").arg(wordCount));
}

void MainWindow::updateSaveStatus()
{
    saveLabel->setStyleSheet("color: #EA3C53; padding-left: 5px; font-size: 12px; qproperty-alignment: AlignCenter;");
    saveLabel->setText("NOT SAVED");
}

void MainWindow::save()
{
    if (ui->textEdit->toPlainText().isEmpty())
    {
        // If the textEdit is empty, do not save
        return;
    }
    // Save the content of textEdit to a file
    // If currentSavePath is empty, prompt the user to choose a save location
    if (currentSavePath.isEmpty())
    {
        // If no path is set, prompt the user to choose a save location
        currentSavePath = QFileDialog::getSaveFileName(this, "Save Note", "", "Text Files (*.txt);;All Files (*)");
        if (currentSavePath.isEmpty())
            return; // User cancelled the save dialog

        // Ensure .txt extension
        if (!currentSavePath.endsWith(".txt", Qt::CaseInsensitive))
        {
            currentSavePath += ".txt";
        }
    }

    // autosave functionality
    //  If the autosave timer is not active, start it. Saves every minute
    if (autosaveTimer && !autosaveTimer->isActive())
        autosaveTimer->start(60000); // 1 minute

    // Open the file for writing
    // If the file does not exist, it will be created
    // If it exists, it will be overwritten
    QFile file(currentSavePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        file.close();
        saveLabel->setStyleSheet("color: #A8E4A0; padding-left: 5px; font-size: 12px; qproperty-alignment: AlignCenter;");
        saveLabel->setText("SAVED");
    }
}

void MainWindow::quit()
{
    QCoreApplication::quit();
}

void MainWindow::allignLeft()
{
    /*
        This function takes the position of the cursor in the textEdit,
        gets the block format of the current block, sets its alignment to left,
        and merges this format with the current cursor.
        Finally, it sets the cursor back to the textEdit.
    */
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::allignMiddle()
{
    /*
        This function takes the position of the cursor in the textEdit,
        gets the block format of the current block, sets its alignment to center,
        and merges this format with the current cursor.
        Finally, it sets the cursor back to the textEdit.
    */
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(blockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::allignRight()
{
    /*
        This function takes the position of the cursor in the textEdit,
        gets the block format of the current block, sets its alignment to right,
        and merges this format with the current cursor.
        Finally, it sets the cursor back to the textEdit.
    */
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    save(); // Save before closing
    QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
