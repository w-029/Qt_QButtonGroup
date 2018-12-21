#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initItemGroup();

    timerId = startTimer(800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initItemGroup()
{
    QButtonGroup* itemGroup = new QButtonGroup;
    ui->cb_assit->setVisible(false);
    itemGroup->addButton(ui->cb_assit, WAITING_TEST);
    itemGroup->addButton(ui->cb_testing, TESTING);
    itemGroup->addButton(ui->cb_result_ok, RESULT_OK);
    itemGroup->addButton(ui->cb_result_ng, RESULT_NG);
    connect(itemGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_clickItem_1(int)));
    mItemGroup[TEST_ITEM_1] = itemGroup;

    QButtonGroup* itemGroup_2 = new QButtonGroup;
    ui->cb_assit_2->setVisible(false);
    itemGroup_2->addButton(ui->cb_assit_2, WAITING_TEST);
    itemGroup_2->addButton(ui->cb_testing_2, TESTING);
    itemGroup_2->addButton(ui->cb_result_ok_2, RESULT_OK);
    itemGroup_2->addButton(ui->cb_result_ng_2, RESULT_NG);
    connect(itemGroup_2, SIGNAL(buttonClicked(int)), this, SLOT(on_clickItem_2(int)));
    mItemGroup[TEST_ITEM_2] = itemGroup_2;

    QButtonGroup* itemGroup_3 = new QButtonGroup;
    ui->cb_assit_3->setVisible(false);
    itemGroup_3->addButton(ui->cb_assit_3, WAITING_TEST);
    itemGroup_3->addButton(ui->cb_testing_3, TESTING);
    itemGroup_3->addButton(ui->cb_result_ok_3, RESULT_OK);
    itemGroup_3->addButton(ui->cb_result_ng_3, RESULT_NG);
    connect(itemGroup_3, SIGNAL(buttonClicked(int)), this, SLOT(on_clickItem_3(int)));
    mItemGroup[TEST_ITEM_3] = itemGroup_3;
}

void MainWindow::on_clickItem_1(int id)
{
    setItemStatus(TEST_ITEM_1, id);
}

void MainWindow::on_clickItem_2(int id)
{
    setItemStatus(TEST_ITEM_2, id);
}

void MainWindow::on_clickItem_3(int id)
{
    setItemStatus(TEST_ITEM_3, id);
}

void MainWindow::setItemStatus(eTestItemIndex item, int status)
{
    qDebug() << "checkBox clicked id: " << i2q(status) << endl;

    switch (status) {
    case TESTING:
        mTesting[item] = true;
        break;
    case RESULT_OK:
    case RESULT_NG:
        mTesting[item] = false;
        break;
    default:
        break;
    }
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timerId) {
        map<eTestItemIndex, bool>::iterator iter;
        for (iter = mTesting.begin(); iter != mTesting.end(); iter++) {
            if (iter->second) {
                twinkle(iter->first);
            }
        }
    }
}

void MainWindow::twinkle(eTestItemIndex item)
{
    if (mItemGroup[item]->button(TESTING)->isChecked()) {
        mItemGroup[item]->button(WAITING_TEST)->setChecked(true);
    }
    else {
         mItemGroup[item]->button(TESTING)->setChecked(true);
    }
}
