#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initItemGroup();
    initExeGroup();

    timerId = startTimer(800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initItemGroup()
{
    /* init group_1 */
    QButtonGroup* itemGroup_1 = new QButtonGroup;
    ui->cb_assit->setVisible(false);
    itemGroup_1->addButton(ui->cb_assit, WAITING_TEST);
    itemGroup_1->addButton(ui->cb_testing, TESTING);
    itemGroup_1->addButton(ui->cb_result_ok, RESULT_OK);
    itemGroup_1->addButton(ui->cb_result_ng, RESULT_NG);
    connect(itemGroup_1, SIGNAL(buttonClicked(int)), this, SLOT(on_clickItem_1(int)));
    mItemGroup[TEST_ITEM_1] = itemGroup_1;

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

    mTestGroup[TEST_GROUP_1] = mItemGroup;

    /* init group_2 */

}

void MainWindow::initExeGroup()
{
    mExeGroup = new QButtonGroup;
    mExeGroup->addButton(ui->pb_exe_group, TEST_GROUP_1);
    connect(mExeGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_clickExe(int)));
}

void MainWindow::on_clickExe(int id)
{
    qDebug() << "ese clicked id: " << i2q(id);

    map<eTestItemIndex, QButtonGroup*> testGroup;
    switch (id) {
    case TEST_GROUP_1:
        testGroup = mTestGroup[TEST_GROUP_1];
        break;
    }

    map<eTestItemIndex, QButtonGroup*>::iterator iter;
    /* clear previous item status */
    for (iter =testGroup.begin(); iter != testGroup.end(); iter++) {
        mTesting[iter->first] = false;
        iter->second->button(WAITING_TEST)->setChecked(true);
    }

    /* start group test */
    for (iter =testGroup.begin(); iter != testGroup.end(); iter++) {
        mTesting[iter->first] = true;
        iter->second->button(TESTING)->setChecked(true);
    }
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
