#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:

    void updateWordCount();
    void updateSaveStatus();

    // keyboard shortcut slots
    void save();
    // void paste();
    void quit();
    void allignLeft();
    void allignMiddle();
    void allignRight();
    // void undo();
    // void uploadTemplate();
    // void printDocument();
    // void openDocument();
    // void newDocument();
    // void findInDocument();
    bool eventFilter(QObject *obj, QEvent *event);
    void jumpBelow();
    void jumpAbove();
    void jumpEndLine();
    void deleteCurrentLine();

private:
    Ui::MainWindow *ui;

    QTimer *autosaveTimer = nullptr; // Timer for auto-saving the document
    QString currentSavePath = "";    // Path of the current file to save. Initially empty, i.e., the file is not saved yet.

    QLabel *wordCountLabel = nullptr; // Status bar word count label
    QLabel *saveLabel = nullptr;  // Status bar save label

    void setupKeyboardShortcuts();
    void setupStatusBar();
    // void makeConnections();
};
#endif // MAINWINDOW_H