#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox_0->setVisible(false);

    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(ui->checkBox_0, -1);
    buttonGroup->addButton(ui->checkBox, 0);
    buttonGroup->addButton(ui->checkBox_1, 1);

    timerId = this->startTimer(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timerId) {
        if (ui->checkBox->isChecked()) {
            /* this is not take effect */
//            ui->checkBox->setChecked(false);

            /* this is pivotal */
            ui->checkBox_0->setChecked(true);
        }
        else {
            ui->checkBox->setChecked(true);
        }
    }
}
