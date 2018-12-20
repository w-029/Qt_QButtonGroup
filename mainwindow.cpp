#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cb_assit->setVisible(false);

    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(ui->cb_assit, -1);
    buttonGroup->addButton(ui->cb_testing, 0);
    buttonGroup->addButton(ui->cb_result_ok, 1);
    buttonGroup->addButton(ui->cb_result_ng, 2);

    connect(ui->pb_test_exe, SIGNAL(clicked()), this, SLOT(on_startTwinkle()));
    connect(ui->cb_testing, SIGNAL(clicked()), this, SLOT(on_startTwinkle()));
    connect(ui->cb_result_ok, SIGNAL(clicked()), this, SLOT(on_endTwinkle()));
    connect(ui->cb_result_ng, SIGNAL(clicked()), this, SLOT(on_endTwinkle()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startTwinkle()
{
    bTwinkle = true;
    ui->cb_testing->setChecked(true);
    timerId = this->startTimer(800);
}

void MainWindow::on_endTwinkle()
{
    bTwinkle = false;
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if (bTwinkle && event->timerId() == timerId) {
        twinkle(ui->cb_testing);
    }
}

void MainWindow::twinkle(QCheckBox* cbTwinkle)
{
    if (ui->cb_testing->isChecked()) {
        /* this will not take effect */
//        ui->cb_testing->setChecked(false);

        /* this is pivotal */
        ui->cb_assit->setChecked(true);
    }
    else {
        cbTwinkle->setChecked(true);
    }
}
