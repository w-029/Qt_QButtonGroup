#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void timerEvent(QTimerEvent* event);

private:
    Ui::MainWindow *ui;
    QButtonGroup* buttonGroup;
    int timerId;
};

#endif // MAINWINDOW_H
