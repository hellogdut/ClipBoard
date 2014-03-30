#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPushButton"
#include "QListWidget"
#include "QLabel"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include <QTimer>
#include "QString"
#include "QVector"
#include "QClipboard"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>
#include <Windows.h>
#include <MyGlobalShortcut/MyGlobalShortCut.h>
#include <ScreenShoot/ScreenShoot.h>
class MainWindow : public QWidget  // 原本继承自 QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:

    void SetItem();      // 初始化按钮并布局按钮
    void ResetListbox(); // 重新加载列表框
    bool IsNewString(const QString str);  // 检测剪贴板中内容是否为新内容

private slots:

    bool    GetClipBoard(QString& str );             //  获取剪贴板内容
    bool    SetClipBoard(const QString* str);             //  设置剪贴板内容
    void    ClearAll();                              //清除所有内容
    bool    AddString(const QString str);  //  添加内容到列表框
    bool    DeleteString();                 //  从列表框中删除内容
    bool    UpString();            //  将选中内容上移
    bool    DownString();          //  将选中内容下移
    bool    ReverseString();            //  转置列表框内容
    bool    ReadStringFromFile();               //  导入
    bool    SaveStringToFile();               //  导出
    void    TimeOut();                  //  处理定时器
    void    DoubleClickList();                  //  处理双击列表事件

    void    mousePressEvent(QMouseEvent *event);


    // 快捷键
    void    F9_activated();
    void    F10_activated();
private:

    //按钮
    QPushButton *clear_btn;
    QPushButton *del_btn;
    QPushButton *up_btn;
    QPushButton *down_btn;
    QPushButton *readfile_btn;
    QPushButton *writefile_btn;
    QPushButton *reverse_btn;
    QPushButton *help_btn;
    QPushButton *exit_btn;
    //列表框
    QListWidget *listbox;
    //提示文本
    QLabel      *label;
    // 定时器
    QTimer      *timer;

    //存储剪贴板内容的容器
    QVector<QString*>    *vector;
    //存储最后一次剪贴板内容
    QString Last_str;
    //快捷键
    MyGlobalShortCut* window_shortcut;
};

#endif // MAINWINDOW_H
