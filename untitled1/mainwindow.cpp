#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow()
{

    //GetClipBoard(Last_str);  // 使忽略当前剪贴板内容
    SetItem();
    window_shortcut = new MyGlobalShortCut("F9",this);
    ss = 0;
    f10_shortcut = new MyGlobalShortCut("F10",this);
    connect(window_shortcut,SIGNAL(activated()),this,SLOT(F9_activated()));
    connect(f10_shortcut,SIGNAL(activated()),this,SLOT(F10_activated()));
    board = QApplication::clipboard();
    connect(board,SIGNAL(dataChanged()),this,SLOT(ClipBoardChange()));


}

MainWindow::~MainWindow()
{

}
void MainWindow::SetItem()
{
    // 初始化容器
    vector = new QVector<QString*>;

    //初始化按钮
    clear_btn    = new QPushButton("清除");
    del_btn      = new QPushButton("删除");
    up_btn       = new QPushButton("上移");
    down_btn     = new QPushButton("下移");
    readfile_btn   = new QPushButton("导入");
    writefile_btn  = new QPushButton("导出");
    reverse_btn  = new QPushButton("倒置");
    help_btn     = new QPushButton("帮助");

    //exit_btn     = new QPushButton("退出");

    //初始化列表框
    listbox      = new QListWidget();
    //初始化提示文本
    label        = new QLabel("当前剪贴板内容");

    //左上布局
    QHBoxLayout *LeftTopLayout = new QHBoxLayout();
    LeftTopLayout ->addWidget(label);
    LeftTopLayout ->addWidget(readfile_btn);
    LeftTopLayout ->addWidget(writefile_btn);
    //左布局
    QVBoxLayout *Left = new QVBoxLayout();
    Left          ->addLayout(LeftTopLayout);
    Left          ->addWidget(listbox);

    //右布局
    QVBoxLayout *RightTopLayout = new QVBoxLayout();
    RightTopLayout ->addWidget(clear_btn);
    RightTopLayout ->addWidget(del_btn);
    RightTopLayout ->addWidget(up_btn);
    RightTopLayout ->addWidget(down_btn);
    RightTopLayout ->addWidget(reverse_btn);
   // RightTopLayout ->addWidget(exit_btn);

    //布局合并
    QHBoxLayout *TopLayout = new QHBoxLayout();
    TopLayout ->addLayout(Left);
    TopLayout ->addLayout(RightTopLayout);
    setLayout(TopLayout);
    //设置窗口大小
    resize(450,600);


    setWindowOpacity(1);
   // setWindowFlags(Qt::FramelessWindowHint);       //设置无边框
    //setAttribute(Qt::WA_TranslucentBackground);  //透明

    //消息绑定
    //connect(timer,SIGNAL(timeout()),this,SLOT(TimeOut()));
    connect(del_btn,SIGNAL(clicked()),this,SLOT(DeleteString()));
    connect(up_btn,SIGNAL(clicked()),this,SLOT(UpString()));
    connect(down_btn,SIGNAL(clicked()),this,SLOT(DownString()));
    connect(readfile_btn,SIGNAL(clicked()),this,SLOT(ReadStringFromFile()));
    connect(writefile_btn,SIGNAL(clicked()),this,SLOT(SaveStringToFile()));
    connect(reverse_btn,SIGNAL(clicked()),this,SLOT(ReverseString()));
    connect(listbox,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(DoubleClickList()));
    connect(clear_btn,SIGNAL(clicked()),this,SLOT(ClearAll()));
    //connect(exit_btn,SIGNAL(clicked()),this,SLOT(close()));

}
void MainWindow::ClipBoardChange()
{

     QString str;
     //获取剪贴板内容
     GetClipBoard(str);
     //如果是新内容则添加
     if(IsNewString(str))
         AddString(str);
}
void MainWindow::ResetListbox()
{
    listbox ->clear();

    for(int i = 0;i < vector->size();i++)
    {
          listbox ->addItem(new QListWidgetItem(QIcon(":/images/64.PNG"), *vector->at(i)));

    }
}
void MainWindow::ClearAll()
{

    // 清除堆中字符串
    for(int i = 0;i < vector->size();i++)
        delete vector->at(i);
    vector->clear();

    // 注意把Last_str清空
    //Last_str = ' ';
    ResetListbox();
}

bool MainWindow::GetClipBoard(QString& str )
{
    QClipboard *board = QApplication::clipboard();
    str = board ->text();
    return true;
}
bool MainWindow::SetClipBoard(const QString* str)
{
    QClipboard *board = QApplication::clipboard();
    board ->setText(*str);
    return true;
}
bool MainWindow::AddString(const QString& str)
{

    if(IsNewString(str))
    {
        // 拷贝剪贴板内容并储存
        QString *t = new QString(str);
        vector ->append(t);
        ResetListbox();
        Last_str = str;
    }
    return true;
}
bool MainWindow::DeleteString()
{

    int i = listbox->currentRow();
    if(i >= 0)
    {
        delete vector->at(i);
        vector ->remove(i);
        ResetListbox();
    }
    //设置焦点
    if(i <= vector ->size() - 1)
        listbox->setCurrentRow(i);
    else
        listbox->setCurrentRow(i - 1);

    return true;
}
bool MainWindow::UpString()
{
    // 上移
    int i = listbox->currentRow();
    if(i > 0)
    {
        QString *tmp = vector ->at(i - 1);
        vector ->replace(i - 1,vector ->at(i));
        vector ->replace(i,tmp);
        ResetListbox();
    }
    //重新设置焦点
    if(i > 0)
        listbox->setCurrentRow(i - 1);
    else
        listbox->setCurrentRow(0);
    return true;
}
bool MainWindow::DownString()
{
    //下移
    int i = listbox->currentRow();
    if((i < vector->size() - 1) && i >= 0)
    {
        QString *tmp = vector ->at(i + 1);
        vector ->replace(i + 1,vector ->at(i));
        vector->replace(i,tmp);
        ResetListbox();
    }
    //重新设置焦点
    if(i < vector->size() - 1 )
        listbox->setCurrentRow(i + 1);
    else
        listbox->setCurrentRow(vector->size() - 1);
    return true;
}

bool MainWindow::ReverseString()
{
    // 郁闷 int 不够用
    long i = 0;
    long j = vector->size() - 1;
    //倒置容器内容
    while(i < j)
    {
       QString* t = vector->at(i);
       vector->replace(i,vector->at(j));
       vector->replace(j,t);
       i++;
       j--;
    }
    ResetListbox();
    listbox ->setCurrentRow(0);
    return true;
}
bool MainWindow::ReadStringFromFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("打开一个文本"), ".", tr("(*.txt)"));

    if(path.length() != 0)
    {
        QFile file(path);    //打开该文本
        file.open(QIODevice::ReadOnly); // 只读模式打开

        QTextStream in(&file);           //创建文件读写流
        QString str;
        QString tmp = Last_str;          // 保存当前剪贴板内容
        while((str = in.readLine())!= NULL) //有行未处理
        {
            AddString(str);
            Last_str = tmp;
        }
        file.close();

    }
    return true;
}
bool MainWindow::SaveStringToFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("选择保存位置"), ".", tr("(*.txt)"));
    if(path.length() != 0)
    {
        QFile file(path);    //打开该文本
        file.open(QIODevice::WriteOnly); // 只写模式打开
        QTextStream out(&file);           //创建文件读写流
        for(int i = 0;i < vector->size();i++)
        {
            out << *vector->at(i) << "\r\n";
        }
        file.close();
    }
    return true;
}
bool MainWindow::IsNewString(const QString& str)
{
    if(str == Last_str)
        return false;
    for(int i = 0;i < vector->size();i++)
        if(*vector->at(i) == str)
            return false;

    return true;
}
void MainWindow::DoubleClickList()
{
   int i = listbox->currentRow();
   SetClipBoard(vector->at(i));
   //提示功能
//   QMessageBox msgbox;
//   msgbox.about(NULL, " ", "复制成功");

}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (ReleaseCapture())
        SendMessage(HWND(this->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    //event->ignore();
}
void MainWindow::F9_activated()
{

    if(this ->isHidden()) // 窗口被隐藏
    {
        //设置窗口置顶
        this ->setWindowFlags(Qt::WindowStaysOnTopHint);
        this ->show();
    }else
        if(this ->isMinimized())// 窗口被最小化
        {

            this->setWindowState(Qt::WindowActive);
            this->activateWindow();
            this->setWindowFlags(Qt::WindowStaysOnTopHint);
            this->show();
        }
    else
        this ->hide();

}
void MainWindow::F10_activated()
{
    ScreenShoot *ss = ScreenShoot::Instance();
    if(ss)
    {
        if(ss->isHidden())
            ss->show();
    }
}
