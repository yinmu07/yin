#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>
#include "chessitem.h"
#include <QMessageBox>

#define CHESS_R 28
#define CHESS_C 28
#define MAX_X 50
#define MAX_Y 50

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);//实时绘制界面
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件

private:
    void InitUI();//初始化界面
    void DrawChessBoard();//画棋盘
    void DrawHandChess();//画鼠标上的棋子
    void DrawChessItem();//绘制棋盘上的棋子
    void DrawChessAtPoint(QPainter &painter,QPoint &point);//画棋子的样式和我位置
    int CountNearItem(ChessItem item,QPoint pt);//判断棋子是否五子连接

private:
    Ui::MainWindow *ui;
    bool b_black;//定义棋子颜色
    QVector<ChessItem> p_ChessItem;//定义棋子个数

};
#endif // MAINWINDOW_H
