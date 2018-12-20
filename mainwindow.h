#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_startTwinkle();
    void on_endTwinkle();

private:
    void timerEvent(QTimerEvent* event);
    void twinkle(QCheckBox* cb);

private:
    Ui::MainWindow *ui;
    QButtonGroup* buttonGroup;
    int timerId;
    bool bTwinkle;
};

#endif // MAINWINDOW_H
