#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


private slots:
    
    //keyboard shortcut slots
    // void save();
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

    void setupKeyboardShortcuts();
   // void makeConnections();
};
#endif // MAINWINDOW_H