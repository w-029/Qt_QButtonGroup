#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QCheckBox>

typedef enum eTestGroupIndex
{
    TEST_GROUP_1 = 0x00,
} eTestGroupIndex;

typedef enum eTestItemIndex
{
    TEST_ITEM_1 = 0x00,
    TEST_ITEM_2 = 0x01,
    TEST_ITEM_3 = 0x02,
} eTestItemIndex;

typedef enum eTestItemStatus
{
    TESTING,
    RESULT_OK,
    RESULT_NG,
    STATUS_COUNT,
} eTestItemStatus;

using namespace std;
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
    void on_clickItem_1(int id);
    void on_clickItem_2(int id);
    void on_clickItem_3(int id);
    void on_clickExe(int id);

private:
    void timerEvent(QTimerEvent* event);
    void initItemGroup();
    void initExeGroup();
    void setItemStatus(eTestItemIndex item, int status);
    void clearItemStatus(eTestItemIndex item);
    void twinkle(eTestItemIndex item);
    string i2s(int i) {return to_string(i);}
    QString s2q(string str) {return QString::fromStdString(str);}
    QString i2q(int i) {return s2q(i2s(i));}

private:
    Ui::MainWindow *ui;
    int timerId;
    QButtonGroup* mExeGroup;
    map<eTestItemIndex, bool> mTesting;
    map<eTestItemIndex, QButtonGroup*> mItemGroup;
    map<eTestGroupIndex, map<eTestItemIndex, QButtonGroup*>> mTestGroup;
};

#endif // MAINWINDOW_H
