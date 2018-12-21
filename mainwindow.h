#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QCheckBox>

typedef enum eTestItemIndex
{
    TEST_ITEM_1 = 0x00,
    TEST_ITEM_2 = 0x01,
    TEST_ITEM_3 = 0x02,
} eTestItemIndex;

typedef enum eTestItemStatus
{
    WAITING_TEST = 0x00,
    TESTING = 0x01,
    RESULT_OK = 0x02,
    RESULT_NG = 0x04,
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

private:
    void timerEvent(QTimerEvent* event);
    void initItemGroup();
    void initExeGroup();
    void setItemStatus(eTestItemIndex item, int status);
    void twinkle(eTestItemIndex item);
    string i2s(int i) {return to_string(i);}
    QString s2q(string str) {return QString::fromStdString(str);}
    QString i2q(int i) {return s2q(i2s(i));}

private:
    Ui::MainWindow *ui;
    int timerId;
    map<eTestItemIndex, QButtonGroup*> mItemGroup;
    map<eTestItemIndex, bool> mTesting;
};

#endif // MAINWINDOW_H
