#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//创建一个app的对象
    MainWindow w;//实例化一个MainWindow
    w.show();//显示MainWindow界面
    return a.exec();//exec 等待消息循环
}
