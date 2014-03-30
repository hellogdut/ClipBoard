#include "mainwindow.h"
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    解决不同平台乱码 Ubuntu下
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));


    MainWindow w;
    w.show();
    return a.exec();
}
