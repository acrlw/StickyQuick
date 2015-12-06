#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void AddNote();
    void DeleteNote();
    void ManageNote();
private:
    Ui::MainWindow *ui;
    int StickyCount = 0;
    QTimer * mTimer;
};

#endif // MAINWINDOW_H
